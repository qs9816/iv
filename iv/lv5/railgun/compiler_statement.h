#ifndef IV_LV5_RAILGUN_COMPILER_STATEMENT_H_
#define IV_LV5_RAILGUN_COMPILER_STATEMENT_H_
#include <iv/lv5/railgun/compiler.h>
namespace iv {
namespace lv5 {
namespace railgun {

inline void Compiler::Visit(const Block* block) {
  BreakTarget jump(this, block);
  const Statements& stmts = block->body();
  for (Statements::const_iterator it = stmts.begin(),
       last = stmts.end(); it != last; ++it) {
    EmitStatement(*it);
    if (continuation_status_.IsDeadStatement()) {
      break;
    }
  }
  jump.EmitJumps(CurrentSize());
  continuation_status_.ResolveJump(block);
}

inline void Compiler::Visit(const FunctionStatement* stmt) {
  const FunctionLiteral* func = stmt->function();
  assert(func->name());  // FunctionStatement must have name
  const Symbol name = func->name().Address()->symbol();
  const uint32_t index = SymbolToNameIndex(name);
  if (IsUsedReference(index)) {
    if (RegisterID local = GetLocal(name)) {
      EmitExpression(func, local);
    } else {
      RegisterID tmp = EmitExpression(func);
      EmitStore(name, tmp);
    }
  }
}

inline void Compiler::Visit(const FunctionDeclaration* func) { }

inline void Compiler::Visit(const Declaration* decl) {
  if (const core::Maybe<const Expression> maybe = decl->expr()) {
    const Symbol sym = decl->name()->symbol();
    const uint32_t index = SymbolToNameIndex(sym);
    const Expression* expr = maybe.Address();
    if (IsUsedReference(index) || !Condition::NoSideEffect(expr)) {
      if (RegisterID local = GetLocal(sym)) {
        EmitExpression(expr, local);
      } else {
        RegisterID tmp = EmitExpression(expr);
        EmitStore(sym, tmp);
      }
    }
  }
}

inline void Compiler::Visit(const VariableStatement* var) {
  const Declarations& decls = var->decls();
  for (Declarations::const_iterator it = decls.begin(),
       last = decls.end(); it != last; ++it) {
    Visit(*it);
  }
}

inline void Compiler::Visit(const EmptyStatement* stmt) { }

inline void Compiler::Visit(const IfStatement* stmt) {
  const Condition::Type cond = Condition::Analyze(stmt->cond());
  std::size_t label = 0;
  if (cond == Condition::COND_INDETERMINATE) {
    RegisterID cond = EmitExpression(stmt->cond());
    label = CurrentSize();
    Emit<OP::IF_FALSE>(0, cond);
  }

  if (const core::Maybe<const Statement> else_stmt = stmt->else_statement()) {
    if (cond != Condition::COND_FALSE) {
      // then statement block
      EmitStatement(stmt->then_statement());
    }

    if (continuation_status_.IsDeadStatement()) {
      continuation_status_.Next();
    } else {
      continuation_status_.Insert(stmt);
    }

    const std::size_t second = CurrentSize();
    if (cond == Condition::COND_INDETERMINATE) {
      Emit<OP::JUMP_BY>(0);  // dummy index
      EmitJump(CurrentSize(), label);
    }

    if (cond != Condition::COND_TRUE) {
      EmitStatement(else_stmt.Address());
    }
    if (continuation_status_.Has(stmt)) {
      continuation_status_.Erase(stmt);
      if (continuation_status_.IsDeadStatement()) {
        continuation_status_.Next();
      }
    }

    if (cond == Condition::COND_INDETERMINATE) {
      EmitJump(CurrentSize(), second);
    }
  } else {
    if (cond == Condition::COND_FALSE) {
      return;
    }
    // then statement block
    EmitStatement(stmt->then_statement());
    if (continuation_status_.IsDeadStatement()) {
      // recover if this IfStatement is not dead code
      continuation_status_.Next();
    }
    if (cond == Condition::COND_INDETERMINATE) {
      EmitJump(CurrentSize(), label);
    }
  }
}

inline void Compiler::Visit(const DoWhileStatement* stmt) {
  ContinueTarget jump(this, stmt);
  const std::size_t start_index = CurrentSize();

  EmitStatement(stmt->body());

  const std::size_t cond_index = CurrentSize();

  {
    RegisterID cond = EmitExpression(stmt->cond());
    Emit<OP::IF_TRUE>(Instruction::Diff(start_index, CurrentSize()), cond);
  }

  jump.EmitJumps(CurrentSize(), cond_index);

  continuation_status_.ResolveJump(stmt);
  if (continuation_status_.IsDeadStatement()) {
    continuation_status_.Next();
  }
}

inline void Compiler::Visit(const WhileStatement* stmt) {
  ContinueTarget jump(this, stmt);
  const std::size_t start_index = CurrentSize();

  const Condition::Type cond = Condition::Analyze(stmt->cond());
  if (cond == Condition::COND_FALSE) {
    // like:
    //  while (false) {
    //  }
    return;
  }

  RegisterID dst;
  if (cond == Condition::COND_INDETERMINATE) {
    dst = EmitExpression(stmt->cond());
  }

  if (stmt->body()->IsEffectiveStatement()) {
    if (cond == Condition::COND_INDETERMINATE) {
      const std::size_t label = CurrentSize();
      Emit<OP::IF_FALSE>(0, dst);
      dst.reset();

      EmitStatement(stmt->body());

      Emit<OP::JUMP_BY>(Instruction::Diff(start_index, CurrentSize()));
      EmitJump(CurrentSize(), label);
    } else {
      assert(cond == Condition::COND_TRUE);

      EmitStatement(stmt->body());

      Emit<OP::JUMP_BY>(Instruction::Diff(start_index, CurrentSize()));
    }
    jump.EmitJumps(CurrentSize(), start_index);
    continuation_status_.ResolveJump(stmt);
  } else {
    if (cond == Condition::COND_INDETERMINATE) {
      Emit<OP::IF_TRUE>(Instruction::Diff(start_index, CurrentSize()), dst);
    } else {
      assert(cond == Condition::COND_TRUE);
      Emit<OP::JUMP_BY>(Instruction::Diff(start_index, CurrentSize()));
    }
  }

  if (continuation_status_.IsDeadStatement()) {
    continuation_status_.Next();
  }
}

inline void Compiler::Visit(const ForStatement* stmt) {
  ContinueTarget jump(this, stmt);

  if (const core::Maybe<const Statement> maybe = stmt->init()) {
    const Statement* init = maybe.Address();
    if (init->AsVariableStatement()) {
      EmitStatement(init);
    } else {
      assert(init->AsExpressionStatement());
      // not evaluate as ExpressionStatement
      // because ExpressionStatement returns statement value
      EmitExpression(init->AsExpressionStatement()->expr());
    }
  }

  const std::size_t start_index = CurrentSize();
  const core::Maybe<const Expression> cond = stmt->cond();
  std::size_t label = 0;

  if (cond) {
    RegisterID dst = EmitExpression(cond.Address());
    label = CurrentSize();
    Emit<OP::IF_FALSE>(0, dst);
  }

  EmitStatement(stmt->body());

  const std::size_t prev_next = CurrentSize();
  if (const core::Maybe<const Expression> next = stmt->next()) {
    EmitExpression(next.Address());
  }

  Emit<OP::JUMP_BY>(Instruction::Diff(start_index, CurrentSize()));

  if (cond) {
    EmitJump(CurrentSize(), label);
  }

  jump.EmitJumps(CurrentSize(), prev_next);

  continuation_status_.ResolveJump(stmt);
  if (continuation_status_.IsDeadStatement()) {
    continuation_status_.Next();
  }
}

inline void Compiler::Visit(const ForInStatement* stmt) {
  ContinueTarget jump(this, stmt);

  const Expression* lhs = NULL;
  Symbol for_decl = symbol::kDummySymbol;
  if (const VariableStatement* var = stmt->each()->AsVariableStatement()) {
    const Declaration* decl = var->decls().front();
    Visit(decl);
    for_decl = decl->name()->symbol();
  } else {
    // LeftHandSideExpression
    assert(stmt->each()->AsExpressionStatement());
    lhs = stmt->each()->AsExpressionStatement()->expr();
  }

  {
    RegisterID iterator = registers_.Acquire();
    std::size_t for_in_setup_jump;
    {
      RegisterID enumerable = EmitExpression(stmt->enumerable());
      for_in_setup_jump = CurrentSize();
      Emit<OP::FORIN_SETUP>(0, iterator, enumerable);
    }

    const std::size_t start_index = CurrentSize();
    {
      if (!lhs || lhs->AsIdentifier()) {
        // Identifier
        if (lhs) {
          for_decl = lhs->AsIdentifier()->symbol();
        }
        if (RegisterID local = GetLocal(for_decl)) {
          const LookupInfo info = Lookup(for_decl);
          if (info.immutable()) {
            local = registers_.Acquire();
          }
          thunklist_.Spill(local);
          Emit<OP::FORIN_ENUMERATE>(0, local, iterator);
          if (code_->strict() && info.immutable()) {
            Emit<OP::RAISE_IMMUTABLE>(SymbolToNameIndex(for_decl));
          }
        } else {
          RegisterID tmp = registers_.Acquire();
          Emit<OP::FORIN_ENUMERATE>(0, tmp, iterator);
          EmitStore(for_decl, tmp);
        }
      } else {
        RegisterID tmp = registers_.Acquire();
        Emit<OP::FORIN_ENUMERATE>(0, tmp, iterator);
        if (lhs->AsPropertyAccess()) {
          // PropertyAccess
          if (const IdentifierAccess* ac = lhs->AsIdentifierAccess()) {
            // IdentifierAccess
            RegisterID base = EmitExpression(ac->target());
            const uint32_t index = SymbolToNameIndex(ac->key());
            Emit<OP::STORE_PROP>(base, index, tmp, 0, 0, 0, 0);
          } else {
            // IndexAccess
            const IndexAccess* idx = lhs->AsIndexAccess();
            const Expression* key = idx->key();
            if (const StringLiteral* str = key->AsStringLiteral()) {
              RegisterID base = EmitExpression(idx->target());
              const uint32_t index =
                  SymbolToNameIndex(context::Intern(ctx_, str->value()));
              Emit<OP::STORE_PROP>(base, index, tmp, 0, 0, 0, 0);
            } else if (const NumberLiteral* num = key->AsNumberLiteral()) {
              RegisterID base = EmitExpression(idx->target());
              const uint32_t index =
                  SymbolToNameIndex(context::Intern(ctx_, num->value()));
              Emit<OP::STORE_PROP>(base, index, tmp, 0, 0, 0, 0);
            } else {
              Thunk base(&thunklist_, EmitExpression(idx->target()));
              RegisterID element = EmitExpression(idx->key());
              Emit<OP::STORE_ELEMENT>(base.Release(), element, tmp);
            }
          }
        } else {
          // FunctionCall
          // ConstructorCall
          tmp.reset();
          EmitExpression(lhs);
          Emit<OP::RAISE_REFERENCE>();
        }
      }
    }

    EmitStatement(stmt->body());

    Emit<OP::JUMP_BY>(Instruction::Diff(start_index, CurrentSize()));

    const std::size_t end_index = CurrentSize();
    EmitJump(end_index, start_index);
    EmitJump(end_index, for_in_setup_jump);

    jump.EmitJumps(end_index, start_index);
  }
  continuation_status_.ResolveJump(stmt);
  if (continuation_status_.IsDeadStatement()) {
    continuation_status_.Next();
  }
}

inline void Compiler::Visit(const ContinueStatement* stmt) {
  const JumpEntry& entry = jump_table_[stmt->target()];
  EmitLevel(CurrentLevel(), std::get<0>(entry));
  const std::size_t arg_index = CurrentSize();
  Emit<OP::JUMP_BY>(0);
  std::get<2>(entry)->push_back(arg_index);
  continuation_status_.JumpTo(stmt->target());
}

inline void Compiler::Visit(const BreakStatement* stmt) {
  if (!stmt->target() && !stmt->label().IsDummy()) {
    // through
  } else {
    const JumpEntry& entry = jump_table_[stmt->target()];
    EmitLevel(CurrentLevel(), std::get<0>(entry));
    const std::size_t arg_index = CurrentSize();
    Emit<OP::JUMP_BY>(0);  // dummy
    std::get<1>(entry)->push_back(arg_index);
  }
  continuation_status_.JumpTo(stmt->target());
}

inline void Compiler::Visit(const ReturnStatement* stmt) {
  RegisterID dst;
  if (const core::Maybe<const Expression> expr = stmt->expr()) {
    dst = EmitExpression(expr.Address());
  } else {
    dst = registers_.Acquire();
    Emit<OP::LOAD_UNDEFINED>(dst);
  }

  if (CurrentLevel() == 0) {
    Emit<OP::RETURN>(dst);
  } else {
    // nested finally has found
    // set finally jump targets
    dst = EmitLevel(CurrentLevel(), 0, dst);
    Emit<OP::RETURN>(dst);
  }
  continuation_status_.Kill();
}

inline void Compiler::Visit(const WithStatement* stmt) {
  {
    RegisterID dst = EmitExpression(stmt->context());
    Emit<OP::WITH_SETUP>(dst);
  }
  PushLevelWith();
  {
    DynamicEnvLevelCounter counter(this);
    current_variable_scope_ =
        std::shared_ptr<VariableScope>(
            new WithScope(current_variable_scope_));
    EmitStatement(stmt->body());
    current_variable_scope_ = current_variable_scope_->upper();
  }
  PopLevel();
  Emit<OP::POP_ENV>();
}

inline void Compiler::Visit(const LabelledStatement* stmt) {
  EmitStatement(stmt->body());
}

inline void Compiler::Visit(const SwitchStatement* stmt) {
  BreakTarget jump(this, stmt);
  typedef SwitchStatement::CaseClauses CaseClauses;
  const CaseClauses& clauses = stmt->clauses();
  bool has_default_clause = false;
  std::size_t label = 0;
  std::vector<std::size_t> indexes(clauses.size());
  {
    RegisterID cond = EmitExpression(stmt->expr(), registers_.Acquire());
    std::vector<std::size_t>::iterator idx = indexes.begin();
    std::vector<std::size_t>::iterator default_it = indexes.end();
    for (CaseClauses::const_iterator it = clauses.begin(),
         last = clauses.end(); it != last; ++it, ++idx) {
      if (const core::Maybe<const Expression> expr = (*it)->expr()) {
        // case
        RegisterID tmp = EmitExpression(expr.Address());
        RegisterID ret = tmp->IsLocal() ? registers_.Acquire() : tmp;
        Emit<OP::BINARY_STRICT_EQ>(ret, cond, tmp);
        *idx = CurrentSize();
        Emit<OP::IF_TRUE>(0, ret);
      } else {
        // default
        default_it = idx;
      }
    }
    if (default_it != indexes.end()) {
      *default_it = CurrentSize();
      has_default_clause = true;
    } else {
      // all cases are not equal and no default case
      label = CurrentSize();
    }
    Emit<OP::JUMP_BY>(0);
  }
  {
    std::vector<std::size_t>::const_iterator idx = indexes.begin();
    for (CaseClauses::const_iterator it = clauses.begin(),
         last = clauses.end(); it != last; ++it, ++idx) {
      EmitJump(CurrentSize(), *idx);
      const Statements& stmts = (*it)->body();
      for (Statements::const_iterator stmt_it = stmts.begin(),
           stmt_last = stmts.end(); stmt_it != stmt_last; ++stmt_it) {
        EmitStatement(*stmt_it);
        if (continuation_status_.IsDeadStatement()) {
          break;
        }
      }
      if (continuation_status_.IsDeadStatement()) {
        if ((it + 1) != last) {
          continuation_status_.Next();
        }
      }
    }
  }
  jump.EmitJumps(CurrentSize());
  if (!has_default_clause) {
    EmitJump(CurrentSize(), label);
  }

  continuation_status_.ResolveJump(stmt);
  if (continuation_status_.IsDeadStatement() && !has_default_clause) {
    continuation_status_.Next();
  }
}

inline void Compiler::Visit(const ThrowStatement* stmt) {
  RegisterID dst = EmitExpression(stmt->expr());
  Emit<OP::THROW>(dst);
  continuation_status_.Kill();
}

inline void Compiler::Visit(const TryStatement* stmt) {
  const std::size_t try_start = CurrentSize();
  const bool has_catch = stmt->catch_block();
  const bool has_finally = stmt->finally_block();
  TryTarget target(this, has_finally);
  RegisterID jmp;
  RegisterID ret;
  RegisterID flag;
  if (has_finally) {
    jmp = registers_.Acquire();
    ret = registers_.Acquire();
    flag = registers_.Acquire();
    std::get<2>(level_stack_.back()) = jmp;
    std::get<3>(level_stack_.back()) = ret;
    std::get<4>(level_stack_.back()) = flag;
  }
  EmitStatement(stmt->body());
  if (has_finally) {
    const std::size_t finally_jump = CurrentSize();
    Emit<OP::JUMP_SUBROUTINE>(0, jmp, flag);
    std::get<1>(level_stack_.back())->push_back(finally_jump);
  }
  const std::size_t label = CurrentSize();
  Emit<OP::JUMP_BY>(0);

  std::size_t catch_return_label_index = 0;
  if (const core::Maybe<const Block> block = stmt->catch_block()) {
    if (continuation_status_.IsDeadStatement()) {
      continuation_status_.Next();
    } else {
      continuation_status_.Insert(stmt);
    }
    const Symbol catch_symbol = stmt->catch_name().Address()->symbol();
    {
      RegisterID error = registers_.Acquire();
      code_->RegisterHandler<Handler::CATCH>(
          try_start,
          CurrentSize(),
          0,
          error->reg(),
          0,
          dynamic_env_level());
      Emit<OP::TRY_CATCH_SETUP>(error, SymbolToNameIndex(catch_symbol));
    }
    PushLevelWith();
    {
      DynamicEnvLevelCounter counter(this);
      current_variable_scope_ =
          std::shared_ptr<VariableScope>(
              new CatchScope(current_variable_scope_, catch_symbol));
      EmitStatement(block.Address());
      current_variable_scope_ = current_variable_scope_->upper();
    }
    PopLevel();
    Emit<OP::POP_ENV>();
    if (has_finally) {
      const std::size_t finally_jump = CurrentSize();
      Emit<OP::JUMP_SUBROUTINE>(0, jmp, flag);
      std::get<1>(level_stack_.back())->push_back(finally_jump);
    }
    catch_return_label_index = CurrentSize();
    Emit<OP::JUMP_BY>(0);

    if (continuation_status_.Has(stmt)) {
      continuation_status_.Erase(stmt);
      if (continuation_status_.IsDeadStatement()) {
        continuation_status_.Next();
      }
    }
  }

  if (const core::Maybe<const Block> block = stmt->finally_block()) {
    const std::size_t finally_start = CurrentSize();
    if (continuation_status_.IsDeadStatement()) {
      continuation_status_.Next();
    } else {
      continuation_status_.Insert(stmt);
    }
    code_->RegisterHandler<Handler::FINALLY>(
        try_start,
        finally_start,
        jmp->reg(),
        ret->reg(),
        flag->reg(),
        dynamic_env_level());
    target.EmitJumps(finally_start);

    EmitStatement(block.Address());
    Emit<OP::RETURN_SUBROUTINE>(jmp, flag);

    if (continuation_status_.Has(stmt)) {
      continuation_status_.Erase(stmt);
    } else {
      if (!continuation_status_.IsDeadStatement()) {
        continuation_status_.Kill();
      }
    }
  }
  // try last
  EmitJump(CurrentSize(), label);
  // catch last
  if (has_catch) {
    EmitJump(CurrentSize(), catch_return_label_index);
  }
}

inline void Compiler::Visit(const DebuggerStatement* stmt) {
  Emit<OP::DEBUGGER>();
}

inline void Compiler::Visit(const ExpressionStatement* stmt) {
  if (current_variable_scope_->UseExpressionReturn()) {
    eval_result_ = EmitExpression(stmt->expr(), eval_result_);
  } else {
    EmitExpression(stmt->expr());
  }
}

inline void Compiler::Visit(const CaseClause* dummy) { }

} } }  // namespace iv::lv5::railgun
#endif  // IV_LV5_RAILGUN_COMPILER_STATEMENT_H_