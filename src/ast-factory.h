#ifndef _IV_AST_FACTORY_H_
#define _IV_AST_FACTORY_H_
#include <tr1/type_traits>
#include "functor.h"
#include "ast.h"
#include "alloc.h"
#include "static_assert.h"
#include "ustringpiece.h"

namespace iv {
namespace core {
namespace ast {

template<std::size_t N, typename Factory>
class BasicAstFactory : public Space<N> {
 public:
  typedef BasicAstFactory<N, Factory> this_type;

#define V(AST) typedef typename ast::AST<Factory> AST;
  AST_NODE_LIST(V)
#undef V
#define V(X, XS) typedef typename SpaceVector<Factory, X*>::type XS;
  AST_LIST_LIST(V)
#undef V
#define V(S) typedef typename SpaceUString<Factory>::type S;
  AST_STRING(V)
#undef V

  BasicAstFactory()
    : Space<N>(),
      undefined_instance_(
          new(static_cast<Factory*>(this))Undefined()),
      empty_statement_instance_(
          new(static_cast<Factory*>(this))EmptyStatement()),
      debugger_statement_instance_(
          new(static_cast<Factory*>(this))DebuggerStatement()),
      this_instance_(
          new(static_cast<Factory*>(this))ThisLiteral()),
      null_instance_(
          new(static_cast<Factory*>(this))NullLiteral()),
      true_instance_(
          new(static_cast<Factory*>(this))TrueLiteral()),
      false_instance_(
          new(static_cast<Factory*>(this))FalseLiteral()) {
    typedef std::tr1::is_convertible<Factory, this_type> is_convertible_to_this;
    typedef std::tr1::is_base_of<this_type, Factory> is_base_of_factory;
    IV_STATIC_ASSERT(is_convertible_to_this::value ||
                     is_base_of_factory::value);
  }

  Identifier* NewIdentifier(const UStringPiece& buffer) {
    return new (static_cast<Factory*>(this))
        Identifier(buffer, static_cast<Factory*>(this));
  }

  Identifier* NewIdentifier(const std::vector<uc16>& buffer) {
    return new (static_cast<Factory*>(this))
        Identifier(buffer, static_cast<Factory*>(this));
  }

  Identifier* NewIdentifier(const std::vector<char>& buffer) {
    return new (static_cast<Factory*>(this))
        Identifier(buffer, static_cast<Factory*>(this));
  }

  NumberLiteral* NewNumberLiteral(const double& val) {
    return new (static_cast<Factory*>(this)) NumberLiteral(val);
  }

  StringLiteral* NewStringLiteral(const std::vector<uc16>& buffer) {
    return new (static_cast<Factory*>(this))
        StringLiteral(buffer, static_cast<Factory*>(this));
  }

  Directivable* NewDirectivable(const std::vector<uc16>& buffer) {
    return new (static_cast<Factory*>(this))
        Directivable(buffer, static_cast<Factory*>(this));
  }

  RegExpLiteral* NewRegExpLiteral(const std::vector<uc16>& content,
                                  const std::vector<uc16>& flags) {
    return new (static_cast<Factory*>(this))
        RegExpLiteral(content, flags, static_cast<Factory*>(this));
  }

  FunctionLiteral* NewFunctionLiteral(typename FunctionLiteral::DeclType type) {
    return new (static_cast<Factory*>(this))
        FunctionLiteral(type, static_cast<Factory*>(this));
  }

  ArrayLiteral* NewArrayLiteral() {
    return new (static_cast<Factory*>(this))
        ArrayLiteral(static_cast<Factory*>(this));
  }

  ObjectLiteral* NewObjectLiteral() {
    return new (static_cast<Factory*>(this))
        ObjectLiteral(static_cast<Factory*>(this));
  }

  Identifiers* NewLabels() {
    return new (Space<N>::New(sizeof(Identifiers)))
        Identifiers(
            typename Identifiers::allocator_type(static_cast<Factory*>(this)));
  }

  NullLiteral* NewNullLiteral() {
    return null_instance_;
  }

  EmptyStatement* NewEmptyStatement() {
    return empty_statement_instance_;
  }

  DebuggerStatement* NewDebuggerStatement() {
    return debugger_statement_instance_;
  }

  ThisLiteral* NewThisLiteral() {
    return this_instance_;
  }

  Undefined* NewUndefined() {
    return undefined_instance_;
  }

  TrueLiteral* NewTrueLiteral() {
    return true_instance_;
  }

  FalseLiteral* NewFalseLiteral() {
    return false_instance_;
  }

  FunctionStatement* NewFunctionStatement(FunctionLiteral* func) {
    return new (static_cast<Factory*>(this)) FunctionStatement(func);
  }

  Block* NewBlock() {
    return new (static_cast<Factory*>(this)) Block(static_cast<Factory*>(this));
  }

  VariableStatement* NewVariableStatement(Token::Type token) {
    return new (static_cast<Factory*>(this))
        VariableStatement(token, static_cast<Factory*>(this));
  }

  Declaration* NewDeclaration(Identifier* name, Expression* expr) {
    return new (static_cast<Factory*>(this)) Declaration(name, expr);
  }

  IfStatement* NewIfStatement(Expression* cond, Statement* then) {
    return new (static_cast<Factory*>(this)) IfStatement(cond, then);
  }

  DoWhileStatement* NewDoWhileStatement() {
    return new (static_cast<Factory*>(this)) DoWhileStatement();
  }

  WhileStatement* NewWhileStatement(Expression* expr) {
    return new (static_cast<Factory*>(this)) WhileStatement(expr);
  }

  ForInStatement* NewForInStatement(Statement* each,
                                    Expression* enumerable) {
    return new (static_cast<Factory*>(this)) ForInStatement(each, enumerable);
  }

  ExpressionStatement* NewExpressionStatement(Expression* expr) {
    return new (static_cast<Factory*>(this)) ExpressionStatement(expr);
  }

  ForStatement* NewForStatement() {
    return new (static_cast<Factory*>(this)) ForStatement();
  }

  ContinueStatement* NewContinueStatement() {
    return new (static_cast<Factory*>(this)) ContinueStatement();
  }

  BreakStatement* NewBreakStatement() {
    return new (static_cast<Factory*>(this)) BreakStatement();
  }

  ReturnStatement* NewReturnStatement(
      Expression* expr) {
    return new (static_cast<Factory*>(this)) ReturnStatement(expr);
  }

  WithStatement* NewWithStatement(
      Expression* expr, Statement* stmt) {
    return new (static_cast<Factory*>(this)) WithStatement(expr, stmt);
  }

  SwitchStatement* NewSwitchStatement(Expression* expr) {
    return new (static_cast<Factory*>(this))
        SwitchStatement(expr, static_cast<Factory*>(this));
  }

  CaseClause* NewCaseClause() {
    return new (static_cast<Factory*>(this))
        CaseClause(static_cast<Factory*>(this));
  }

  ThrowStatement*  NewThrowStatement(Expression* expr) {
    return new (static_cast<Factory*>(this)) ThrowStatement(expr);
  }

  TryStatement* NewTryStatement(Block* block) {
    return new (static_cast<Factory*>(this)) TryStatement(block);
  }

  LabelledStatement* NewLabelledStatement(
      Expression* expr,
      Statement* stmt) {
    return new (static_cast<Factory*>(this)) LabelledStatement(expr, stmt);
  }

  BinaryOperation* NewBinaryOperation(Token::Type op,
                                      Expression* result, Expression* right) {
    return new (static_cast<Factory*>(this)) BinaryOperation(op, result, right);
  }

  Assignment* NewAssignment(Token::Type op,
                            Expression* left,
                            Expression* right) {
    return new (static_cast<Factory*>(this)) Assignment(op, left, right);
  }

  ConditionalExpression* NewConditionalExpression(Expression* cond,
                                                  Expression* left,
                                                  Expression* right) {
    return new (static_cast<Factory*>(this))
        ConditionalExpression(cond, left, right);
  }

  UnaryOperation* NewUnaryOperation(Token::Type op, Expression* expr) {
    return new (static_cast<Factory*>(this)) UnaryOperation(op, expr);
  }

  PostfixExpression* NewPostfixExpression(
      Token::Type op, Expression* expr) {
    return new (static_cast<Factory*>(this)) PostfixExpression(op, expr);
  }

  FunctionCall* NewFunctionCall(Expression* expr) {
    return new (static_cast<Factory*>(this))
        FunctionCall(expr, static_cast<Factory*>(this));
  }

  ConstructorCall* NewConstructorCall(Expression* target) {
    return new (static_cast<Factory*>(this))
        ConstructorCall(target, static_cast<Factory*>(this));
  }

  IndexAccess* NewIndexAccess(Expression* expr,
                              Expression* index) {
    return new (static_cast<Factory*>(this)) IndexAccess(expr, index);
  }

  IdentifierAccess* NewIdentifierAccess(Expression* expr,
                                        Identifier* ident) {
    return new (static_cast<Factory*>(this)) IdentifierAccess(expr, ident);
  }

 private:
  Undefined* undefined_instance_;
  EmptyStatement* empty_statement_instance_;
  DebuggerStatement* debugger_statement_instance_;
  ThisLiteral* this_instance_;
  NullLiteral* null_instance_;
  TrueLiteral* true_instance_;
  FalseLiteral* false_instance_;
};

} } }  // namespace iv::core::ast
#endif  // _IV_AST_FACTORY_H_
