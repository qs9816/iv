#ifndef _IV_AST_H_
#define _IV_AST_H_
#include <vector>
#include <tr1/unordered_map>
#include <tr1/tuple>
#include "uchar.h"
#include "noncopyable.h"
#include "utils.h"
#include "space.h"
#include "functor.h"
#include "token.h"
#include "ast-fwd.h"
#include "ast-visitor.h"
#include "source.h"
#include "ustringpiece.h"

namespace iv {
namespace core {
namespace ast {
#define ACCEPT_VISITOR \
  inline void Accept(\
      typename AstVisitor<Factory>::type* visitor) {\
    visitor->Visit(this);\
  }\
  inline void Accept(\
      typename AstVisitor<Factory>::const_type * visitor) const {\
    visitor->Visit(this);\
  }

#define DECLARE_NODE_TYPE(type) \
  inline const type<Factory>* As##type() const { return this; }\
  inline type<Factory>* As##type() { return this; }

#define DECLARE_NODE_TYPE_BASE(type) \
  inline virtual const type<Factory>* As##type() const { return NULL; }\
  inline virtual type<Factory>* As##type() { return NULL; }

template<typename Factory>
class Scope : public SpaceObject,
              private Noncopyable<Scope<Factory> >::type {
 public:
  typedef std::pair<Identifier<Factory>*, bool> Variable;
  typedef typename SpaceVector<Factory, Variable>::type Variables;
  typedef typename SpaceVector<
            Factory,
            FunctionLiteral<Factory>*>::type FunctionLiterals;
  typedef Scope<Factory> this_type;

  explicit Scope(Factory* factory)
    : up_(NULL),
      vars_(typename Variables::allocator_type(factory)),
      funcs_(typename FunctionLiterals::allocator_type(factory)) {
  }
  void AddUnresolved(Identifier<Factory>* name, bool is_const) {
    vars_.push_back(std::make_pair(name, is_const));
  }
  void AddFunctionDeclaration(FunctionLiteral<Factory>* func) {
    funcs_.push_back(func);
  }
  void SetUpperScope(this_type* scope) {
    up_ = scope;
  }
  inline const FunctionLiterals& function_declarations() const {
    return funcs_;
  }
  inline const Variables& variables() const {
    return vars_;
  }
  this_type* GetUpperScope() {
    return up_;
  }
 protected:
  this_type* up_;
  Variables vars_;
  FunctionLiterals funcs_;
};

template<typename Factory>
class AstNode : public SpaceObject,
                private Noncopyable<AstNode<Factory> >::type {
 public:
  virtual ~AstNode() = 0;

  DECLARE_NODE_TYPE_BASE(Statement)
  DECLARE_NODE_TYPE_BASE(Block)
  DECLARE_NODE_TYPE_BASE(ExpressionStatement)
  DECLARE_NODE_TYPE_BASE(EmptyStatement)
  DECLARE_NODE_TYPE_BASE(VariableStatement)
  DECLARE_NODE_TYPE_BASE(DebuggerStatement)
  DECLARE_NODE_TYPE_BASE(FunctionStatement)
  DECLARE_NODE_TYPE_BASE(IfStatement)
  DECLARE_NODE_TYPE_BASE(IterationStatement)
  DECLARE_NODE_TYPE_BASE(DoWhileStatement)
  DECLARE_NODE_TYPE_BASE(WhileStatement)
  DECLARE_NODE_TYPE_BASE(ForStatement)
  DECLARE_NODE_TYPE_BASE(ForInStatement)
  DECLARE_NODE_TYPE_BASE(ContinueStatement)
  DECLARE_NODE_TYPE_BASE(BreakStatement)
  DECLARE_NODE_TYPE_BASE(ReturnStatement)
  DECLARE_NODE_TYPE_BASE(WithStatement)
  DECLARE_NODE_TYPE_BASE(LabelledStatement)
  DECLARE_NODE_TYPE_BASE(SwitchStatement)
  DECLARE_NODE_TYPE_BASE(ThrowStatement)
  DECLARE_NODE_TYPE_BASE(TryStatement)
  DECLARE_NODE_TYPE_BASE(BreakableStatement)
  DECLARE_NODE_TYPE_BASE(NamedOnlyBreakableStatement)
  DECLARE_NODE_TYPE_BASE(AnonymousBreakableStatement)

  DECLARE_NODE_TYPE_BASE(Expression)

  DECLARE_NODE_TYPE_BASE(Literal)
  DECLARE_NODE_TYPE_BASE(ThisLiteral)
  DECLARE_NODE_TYPE_BASE(NullLiteral)
  DECLARE_NODE_TYPE_BASE(FalseLiteral)
  DECLARE_NODE_TYPE_BASE(TrueLiteral)
  DECLARE_NODE_TYPE_BASE(Undefined)
  DECLARE_NODE_TYPE_BASE(NumberLiteral)
  DECLARE_NODE_TYPE_BASE(StringLiteral)
  DECLARE_NODE_TYPE_BASE(Directivable)
  DECLARE_NODE_TYPE_BASE(Identifier)
  DECLARE_NODE_TYPE_BASE(RegExpLiteral)
  DECLARE_NODE_TYPE_BASE(ArrayLiteral)
  DECLARE_NODE_TYPE_BASE(ObjectLiteral)
  DECLARE_NODE_TYPE_BASE(FunctionLiteral)

  DECLARE_NODE_TYPE_BASE(UnaryOperation)
  DECLARE_NODE_TYPE_BASE(PostfixExpression)
  DECLARE_NODE_TYPE_BASE(Assignment)
  DECLARE_NODE_TYPE_BASE(BinaryOperation)
  DECLARE_NODE_TYPE_BASE(ConditionalExpression)
  DECLARE_NODE_TYPE_BASE(PropertyAccess)
  DECLARE_NODE_TYPE_BASE(IdentifierAccess)
  DECLARE_NODE_TYPE_BASE(IndexAccess)
  DECLARE_NODE_TYPE_BASE(Call)
  DECLARE_NODE_TYPE_BASE(FunctionCall)
  DECLARE_NODE_TYPE_BASE(ConstructorCall)

  virtual void Accept(
      typename AstVisitor<Factory>::type* visitor) = 0;
  virtual void Accept(
      typename AstVisitor<Factory>::const_type* visitor) const = 0;
};

template<typename Factory>
inline AstNode<Factory>::~AstNode() { }

#undef DECLARE_NODE_TYPE_BASE
//  Statement
//    : Block
//    | FunctionStatement
//    | VariableStatement
//    | EmptyStatement
//    | ExpressionStatement
//    | IfStatement
//    | IterationStatement
//    | ContinueStatement
//    | BreakStatement
//    | ReturnStatement
//    | WithStatement
//    | LabelledStatement
//    | SwitchStatement
//    | ThrowStatement
//    | TryStatement
//    | DebuggerStatement

// Expression
template<typename Factory>
class Expression : public AstNode<Factory> {
 public:
  inline virtual bool IsValidLeftHandSide() const { return false; }
  DECLARE_NODE_TYPE(Expression)
};

template<typename Factory>
class Literal : public Expression<Factory> {
 public:
  DECLARE_NODE_TYPE(Literal)
};

template<typename Factory>
class Statement : public AstNode<Factory> {
 public:
  DECLARE_NODE_TYPE(Statement)
};

template<typename Factory>
class BreakableStatement : public Statement<Factory> {
 public:
  typedef typename SpaceVector<Factory, Identifier<Factory>*>::type Identifiers;
  BreakableStatement() : labels_(NULL) { }
  void set_labels(Identifiers* labels) {
    labels_ = labels;
  }
  Identifiers* labels() const {
    return labels_;
  }
  DECLARE_NODE_TYPE(BreakableStatement)
 protected:
  Identifiers* labels_;
};

template<typename Factory>
class NamedOnlyBreakableStatement : public BreakableStatement<Factory> {
 public:
  DECLARE_NODE_TYPE(NamedOnlyBreakableStatement)
};

template<typename Factory>
class AnonymousBreakableStatement : public BreakableStatement<Factory> {
 public:
  DECLARE_NODE_TYPE(AnonymousBreakableStatement)
};

template<typename Factory>
class Block : public NamedOnlyBreakableStatement<Factory> {
 public:
  typedef typename SpaceVector<Factory, Statement<Factory>*>::type Statements;
  explicit Block(Factory* factory)
     : body_(typename Statements::allocator_type(factory)) { }

  void AddStatement(Statement<Factory>* stmt) {
    body_.push_back(stmt);
  }

  inline const Statements& body() const {
    return body_;
  }
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(Block)
 private:
  Statements body_;
};

template<typename Factory>
class FunctionStatement : public Statement<Factory> {
 public:
  explicit FunctionStatement(FunctionLiteral<Factory>* func)
    : function_(func) {
  }
  inline FunctionLiteral<Factory>* function() const {
    return function_;
  }
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(FunctionStatement)
 private:
  FunctionLiteral<Factory>* function_;
};

template<typename Factory>
class VariableStatement : public Statement<Factory> {
 public:
  typedef typename SpaceVector<
            Factory,
            Declaration<Factory>*>::type Declarations;
  VariableStatement(Token::Type type, Factory* factory)
    : is_const_(type == Token::CONST),
      decls_(typename Declarations::allocator_type(factory)) { }

  void AddDeclaration(Declaration<Factory>* decl) {
    decls_.push_back(decl);
  }

  inline const Declarations& decls() const {
    return decls_;
  }
  inline bool IsConst() const {
    return is_const_;
  }
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(VariableStatement)
 private:
  const bool is_const_;
  Declarations decls_;
};

template<typename Factory>
class Declaration : public AstNode<Factory> {
 public:
  Declaration(Identifier<Factory>* name, Expression<Factory>* expr)
    : name_(name),
      expr_(expr) {
  }
  inline Identifier<Factory>* name() const {
    return name_;
  }
  inline Expression<Factory>* expr() const {
    return expr_;
  }
  ACCEPT_VISITOR
 private:
  Identifier<Factory>* name_;
  Expression<Factory>* expr_;
};

template<typename Factory>
class EmptyStatement : public Statement<Factory> {
 public:
  DECLARE_NODE_TYPE(EmptyStatement)
  ACCEPT_VISITOR
};

template<typename Factory>
class IfStatement : public Statement<Factory> {
 public:
  IfStatement(Expression<Factory>* cond, Statement<Factory>* then)
    : cond_(cond),
      then_(then),
      else_(NULL) {
  }
  void SetElse(Statement<Factory>* stmt) {
    else_ = stmt;
  }
  inline Expression<Factory>* cond() const { return cond_; }
  inline Statement<Factory>* then_statement() const { return then_; }
  inline Statement<Factory>* else_statement() const { return else_; }
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(IfStatement)
 private:
  Expression<Factory>* cond_;
  Statement<Factory>* then_;
  Statement<Factory>* else_;
};

template<typename Factory>
class IterationStatement : public AnonymousBreakableStatement<Factory> {
 public:
  IterationStatement()
    : body_(NULL) {
  }
  inline Statement<Factory>* body() const { return body_; }
  inline void set_body(Statement<Factory>* stmt) {
    body_ = stmt;
  }
  DECLARE_NODE_TYPE(IterationStatement)
 private:
  Statement<Factory>* body_;
};

template<typename Factory>
class DoWhileStatement : public IterationStatement<Factory> {
 public:
  DoWhileStatement()
    : IterationStatement<Factory>(),
      cond_(NULL) {
  }
  inline Expression<Factory>* cond() const { return cond_; }
  inline void set_cond(Expression<Factory>* expr) {
    cond_ = expr;
  }
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(DoWhileStatement)
 private:
  Expression<Factory>* cond_;
};

template<typename Factory>
class WhileStatement : public IterationStatement<Factory> {
 public:
  explicit WhileStatement(Expression<Factory>* cond)
    : IterationStatement<Factory>(),
      cond_(cond) {
  }
  inline Expression<Factory>* cond() const { return cond_; }
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(WhileStatement)
 private:
  Expression<Factory>* cond_;
};

template<typename Factory>
class ForStatement : public IterationStatement<Factory> {
 public:
  ForStatement()
    : IterationStatement<Factory>(),
      init_(NULL),
      cond_(NULL),
      next_(NULL) {
  }
  inline void SetInit(Statement<Factory>* init) { init_ = init; }
  inline void SetCondition(Expression<Factory>* cond) { cond_ = cond; }
  inline void SetNext(Statement<Factory>* next) { next_ = next; }
  inline Statement<Factory>* init() const { return init_; }
  inline Expression<Factory>* cond() const { return cond_; }
  inline Statement<Factory>* next() const { return next_; }
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(ForStatement)
 private:
  Statement<Factory>* init_;
  Expression<Factory>* cond_;
  Statement<Factory>* next_;
};

template<typename Factory>
class ForInStatement : public IterationStatement<Factory> {
 public:
  ForInStatement(Statement<Factory>* each,
                 Expression<Factory>* enumerable)
    : IterationStatement<Factory>(),
      each_(each),
      enumerable_(enumerable) {
  }
  inline Statement<Factory>* each() const { return each_; }
  inline Expression<Factory>* enumerable() const { return enumerable_; }
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(ForInStatement)
 private:
  Statement<Factory>* each_;
  Expression<Factory>* enumerable_;
};

template<typename Factory>
class ContinueStatement : public Statement<Factory> {
 public:
  ContinueStatement()
    : label_(NULL) {
  }

  void SetLabel(Identifier<Factory>* label) {
    label_ = label;
  }

  void SetTarget(IterationStatement<Factory>* target) {
    target_ = target;
  }
  inline Identifier<Factory>* label() const { return label_; }
  inline IterationStatement<Factory>* target() const { return target_; }
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(ContinueStatement)
 private:
  Identifier<Factory>* label_;
  IterationStatement<Factory>* target_;
};

template<typename Factory>
class BreakStatement : public Statement<Factory> {
 public:
  BreakStatement()
    : label_(NULL),
      target_(NULL) {
  }

  void SetLabel(Identifier<Factory>* label) {
    label_ = label;
  }

  void SetTarget(BreakableStatement<Factory>* target) {
    target_ = target;
  }
  inline Identifier<Factory>* label() const { return label_; }
  inline BreakableStatement<Factory>* target() const { return target_; }
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(BreakStatement)
 private:
  Identifier<Factory>* label_;
  BreakableStatement<Factory>* target_;
};

template<typename Factory>
class ReturnStatement : public Statement<Factory> {
 public:
  explicit ReturnStatement(Expression<Factory>* expr)
    : expr_(expr) {
  }
  inline Expression<Factory>* expr() const { return expr_; }
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(ReturnStatement)
 private:
  Expression<Factory>* expr_;
};

template<typename Factory>
class WithStatement : public Statement<Factory> {
 public:
  WithStatement(Expression<Factory>* context,
                Statement<Factory>* body)
    : context_(context),
      body_(body) {
  }
  inline Expression<Factory>* context() const { return context_; }
  inline Statement<Factory>* body() const { return body_; }
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(WithStatement)
 private:
  Expression<Factory>* context_;
  Statement<Factory>* body_;
};

template<typename Factory>
class LabelledStatement : public Statement<Factory> {
 public:
  LabelledStatement(Expression<Factory>* expr, Statement<Factory>* body)
    : body_(body) {
    label_ = expr->AsLiteral()->AsIdentifier();
  }
  inline Identifier<Factory>* label() const { return label_; }
  inline Statement<Factory>* body() const { return body_; }
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(LabelledStatement)
 private:
  Identifier<Factory>* label_;
  Statement<Factory>* body_;
};

template<typename Factory>
class CaseClause : public AstNode<Factory> {
 public:
  typedef typename SpaceVector<Factory, Statement<Factory>*>::type Statements;
  explicit CaseClause(Factory* factory)
    : expr_(NULL),
      body_(typename Statements::allocator_type(factory)),
      default_(false) {
  }

  void SetExpression(Expression<Factory>* expr) {
    expr_ = expr;
  }

  void SetDefault() {
    default_ = true;
  }

  void AddStatement(Statement<Factory>* stmt) {
    body_.push_back(stmt);
  }
  inline bool IsDefault() const {
    return default_;
  }
  inline Expression<Factory>* expr() const {
    return expr_;
  }
  inline const Statements& body() const {
    return body_;
  }
  ACCEPT_VISITOR
 private:
  Expression<Factory>* expr_;
  Statements body_;
  bool default_;
};

template<typename Factory>
class SwitchStatement : public AnonymousBreakableStatement<Factory> {
 public:
  typedef typename SpaceVector<Factory, CaseClause<Factory>*>::type CaseClauses;
  SwitchStatement(Expression<Factory>* expr,
                  Factory* factory)
    : expr_(expr),
      clauses_(typename CaseClauses::allocator_type(factory)) {
  }

  void AddCaseClause(CaseClause<Factory>* clause) {
    clauses_.push_back(clause);
  }
  inline Expression<Factory>* expr() const { return expr_; }
  inline const CaseClauses& clauses() const { return clauses_; }
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(SwitchStatement)
 private:
  Expression<Factory>* expr_;
  CaseClauses clauses_;
};

template<typename Factory>
class ThrowStatement : public Statement<Factory> {
 public:
  explicit ThrowStatement(Expression<Factory>* expr)
    : expr_(expr) {
  }
  inline Expression<Factory>* expr() const { return expr_; }
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(ThrowStatement)
 private:
  Expression<Factory>* expr_;
};

template<typename Factory>
class TryStatement : public Statement<Factory> {
 public:
  explicit TryStatement(Block<Factory>* block)
    : body_(block),
      catch_name_(NULL),
      catch_block_(NULL),
      finally_block_(NULL) {
  }

  void SetCatch(Identifier<Factory>* name, Block<Factory>* block) {
    catch_name_ = name;
    catch_block_ = block;
  }

  void SetFinally(Block<Factory>* block) {
    finally_block_ = block;
  }
  inline Block<Factory>* body() const { return body_; }
  inline Identifier<Factory>* catch_name() const { return catch_name_; }
  inline Block<Factory>* catch_block() const { return catch_block_; }
  inline Block<Factory>* finally_block() const { return finally_block_; }
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(TryStatement)
 private:
  Block<Factory>* body_;
  Identifier<Factory>* catch_name_;
  Block<Factory>* catch_block_;
  Block<Factory>* finally_block_;
};

template<typename Factory>
class DebuggerStatement : public Statement<Factory> {
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(DebuggerStatement)
};

template<typename Factory>
class ExpressionStatement : public Statement<Factory> {
 public:
  explicit ExpressionStatement(Expression<Factory>* expr) : expr_(expr) { }
  inline Expression<Factory>* expr() const { return expr_; }
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(ExpressionStatement)
 private:
  Expression<Factory>* expr_;
};

template<typename Factory>
class Assignment : public Expression<Factory> {
 public:
  Assignment(Token::Type op,
             Expression<Factory>* left, Expression<Factory>* right)
    : op_(op),
      left_(left),
      right_(right) {
  }
  inline Token::Type op() const { return op_; }
  inline Expression<Factory>* left() const { return left_; }
  inline Expression<Factory>* right() const { return right_; }
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(Assignment)
 private:
  Token::Type op_;
  Expression<Factory>* left_;
  Expression<Factory>* right_;
};

template<typename Factory>
class BinaryOperation : public Expression<Factory> {
 public:
  BinaryOperation(Token::Type op,
                  Expression<Factory>* left, Expression<Factory>* right)
    : op_(op),
      left_(left),
      right_(right) {
  }
  inline Token::Type op() const { return op_; }
  inline Expression<Factory>* left() const { return left_; }
  inline Expression<Factory>* right() const { return right_; }
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(BinaryOperation)
 private:
  Token::Type op_;
  Expression<Factory>* left_;
  Expression<Factory>* right_;
};

template<typename Factory>
class ConditionalExpression : public Expression<Factory> {
 public:
  ConditionalExpression(Expression<Factory>* cond,
                        Expression<Factory>* left,
                        Expression<Factory>* right)
    : cond_(cond), left_(left), right_(right) {
  }
  inline Expression<Factory>* cond() const { return cond_; }
  inline Expression<Factory>* left() const { return left_; }
  inline Expression<Factory>* right() const { return right_; }
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(ConditionalExpression)
 private:
  Expression<Factory>* cond_;
  Expression<Factory>* left_;
  Expression<Factory>* right_;
};

template<typename Factory>
class UnaryOperation : public Expression<Factory> {
 public:
  UnaryOperation(Token::Type op, Expression<Factory>* expr)
    : op_(op),
      expr_(expr) {
  }
  inline Token::Type op() const { return op_; }
  inline Expression<Factory>* expr() const { return expr_; }
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(UnaryOperation)
 private:
  Token::Type op_;
  Expression<Factory>* expr_;
};

template<typename Factory>
class PostfixExpression : public Expression<Factory> {
 public:
  PostfixExpression(Token::Type op, Expression<Factory>* expr)
    : op_(op),
      expr_(expr) {
  }
  inline Token::Type op() const { return op_; }
  inline Expression<Factory>* expr() const { return expr_; }
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(PostfixExpression)
 private:
  Token::Type op_;
  Expression<Factory>* expr_;
};

template<typename Factory>
class StringLiteral : public Literal<Factory> {
 public:
  StringLiteral(const std::vector<uc16>& buffer,
                Factory* factory)
    : value_(buffer.data(),
             buffer.size(),
             typename SpaceUString<Factory>::type::allocator_type(factory)) {
  }

  inline const typename SpaceUString<Factory>::type& value() const {
    return value_;
  }
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(StringLiteral)
 private:
  const typename SpaceUString<Factory>::type value_;
};

template<typename Factory>
class Directivable : public StringLiteral<Factory> {
 public:
  explicit Directivable(const std::vector<uc16>& buffer,
                        Factory* factory)
    : StringLiteral<Factory>(buffer, factory) { }
  DECLARE_NODE_TYPE(Directivable)
};

template<typename Factory>
class NumberLiteral : public Literal<Factory> {
 public:
  explicit NumberLiteral(const double & val)
    : value_(val) {
  }
  inline double value() const { return value_; }
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(NumberLiteral)
 private:
  double value_;
};

template<typename Factory>
class Identifier : public Literal<Factory> {
 public:
  typedef typename SpaceUString<Factory>::type value_type;
  Identifier(const UStringPiece& buffer, Factory* factory)
    : value_(buffer.data(),
             buffer.size(),
             typename value_type::allocator_type(factory)) {
    }
  Identifier(const std::vector<uc16>& buffer, Factory* factory)
    : value_(buffer.data(),
             buffer.size(),
             typename value_type::allocator_type(factory)) {
  }
  Identifier(const std::vector<char>& buffer, Factory* factory)
    : value_(buffer.begin(),
             buffer.end(),
             typename value_type::allocator_type(factory)) {
  }
  inline const value_type& value() const {
    return value_;
  }
  inline bool IsValidLeftHandSide() const { return true; }
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(Identifier)
 protected:
  value_type value_;
};

template<typename Factory>
class IdentifierKey {
 public:
  typedef Identifier<Factory> value_type;
  typedef IdentifierKey<Factory> this_type;
  IdentifierKey(value_type* ident)  // NOLINT
    : ident_(ident) { }
  IdentifierKey(const this_type& rhs)  // NOLINT
    : ident_(rhs.ident_) { }
  inline const typename value_type::value_type& value() const {
    return ident_->value();
  }
  inline bool operator==(const this_type& rhs) const {
    if (ident_ == rhs.ident_) {
      return true;
    } else {
      return value() == rhs.value();
    }
  }
  inline bool operator>(const this_type& rhs) const {
    return value() > rhs.value();
  }
  inline bool operator<(const this_type& rhs) const {
    return value() < rhs.value();
  }
  inline bool operator>=(const this_type& rhs) const {
    return value() >= rhs.value();
  }
  inline bool operator<=(const this_type& rhs) const {
    return value() <= rhs.value();
  }
 private:
  value_type* ident_;
};

template<typename Factory>
class ThisLiteral : public Literal<Factory> {
 public:
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(ThisLiteral)
};

template<typename Factory>
class NullLiteral : public Literal<Factory> {
 public:
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(NullLiteral)
};

template<typename Factory>
class TrueLiteral : public Literal<Factory> {
 public:
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(TrueLiteral)
};

template<typename Factory>
class FalseLiteral : public Literal<Factory> {
 public:
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(FalseLiteral)
};

template<typename Factory>
class Undefined : public Literal<Factory> {
 public:
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(Undefined)
};

template<typename Factory>
class RegExpLiteral : public Literal<Factory> {
 public:
  typedef typename SpaceUString<Factory>::type value_type;

  RegExpLiteral(const std::vector<uc16>& buffer,
                const std::vector<uc16>& flags,
                Factory* factory)
    : value_(buffer.data(),
             buffer.size(), typename value_type::allocator_type(factory)),
      flags_(flags.data(),
             flags.size(), typename value_type::allocator_type(factory)) {
  }
  inline const value_type& value() const { return value_; }
  inline const value_type& flags() const { return flags_; }
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(RegExpLiteral)
 protected:
  value_type value_;
  value_type flags_;
};

template<typename Factory>
class ArrayLiteral : public Literal<Factory> {
 public:
  typedef typename SpaceVector<Factory, Expression<Factory>*>::type Expressions;

  explicit ArrayLiteral(Factory* factory)
    : items_(typename Expressions::allocator_type(factory)) {
  }
  inline void AddItem(Expression<Factory>* expr) {
    items_.push_back(expr);
  }
  inline const Expressions& items() const {
    return items_;
  }
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(ArrayLiteral)
 private:
  Expressions items_;
};

template<typename Factory>
class ObjectLiteral : public Literal<Factory> {
 public:
  enum PropertyDescriptorType {
    DATA = 1,
    GET  = 2,
    SET  = 4
  };
  typedef std::tr1::tuple<PropertyDescriptorType,
                          Identifier<Factory>*,
                          Expression<Factory>*> Property;
  typedef typename SpaceVector<Factory, Property>::type Properties;
  explicit ObjectLiteral(Factory* factory)
    : properties_(typename Properties::allocator_type(factory)) {
  }

  inline void AddDataProperty(Identifier<Factory>* key,
                              Expression<Factory>* val) {
    AddPropertyDescriptor(DATA, key, val);
  }
  inline void AddAccessor(PropertyDescriptorType type,
                          Identifier<Factory>* key,
                          Expression<Factory>* val) {
    AddPropertyDescriptor(type, key, val);
  }
  inline const Properties& properties() const {
    return properties_;
  }
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(ObjectLiteral)
 private:
  inline void AddPropertyDescriptor(PropertyDescriptorType type,
                                    Identifier<Factory>* key,
                                    Expression<Factory>* val) {
    properties_.push_back(std::tr1::make_tuple(type, key, val));
  }
  Properties properties_;
};

template<typename Factory>
class FunctionLiteral : public Literal<Factory> {
 public:
  typedef typename SpaceVector<Factory, Statement<Factory>*>::type Statements;
  typedef typename SpaceVector<Factory, Identifier<Factory>*>::type Identifiers;
  enum DeclType {
    DECLARATION,
    STATEMENT,
    EXPRESSION,
    GLOBAL
  };
  enum ArgType {
    GENERAL,
    SETTER,
    GETTER
  };
  inline void SetName(Identifier<Factory>* name) { name_ = name; }
  inline Identifier<Factory>* name() const {
    return name_;
  }
  inline DeclType type() const { return type_; }
  inline const Identifiers& params() const {
    return params_;
  }
  inline const Statements& body() const {
    return body_;
  }
  inline Scope<Factory>* scope() {
    return &scope_;
  }
  inline const Scope<Factory>& scope() const {
    return scope_;
  }
  inline void set_start_position(std::size_t start) {
    start_position_ = start;
  }
  inline void set_end_position(std::size_t end) {
    end_position_ = end;
  }
  inline std::size_t start_position() const {
    return start_position_;
  }
  inline std::size_t end_position() const {
    return end_position_;
  }
  inline bool strict() const {
    return strict_;
  }
  inline void set_strict(bool strict) {
    strict_ = strict;
  }
  inline void SubStringSource(BasicSource* src) {
    source_ = src->SubString(start_position_,
                             end_position_ - start_position_ + 1);
  }
  inline UStringPiece GetSource() const {
    return source_;
  }
  FunctionLiteral(DeclType type, Factory* factory)
    : name_(NULL),
      type_(type),
      params_(typename Identifiers::allocator_type(factory)),
      body_(typename Statements::allocator_type(factory)),
      scope_(factory),
      strict_(false) {
  }

  void AddParameter(Identifier<Factory>* param) {
    params_.push_back(param);
  }

  void AddStatement(Statement<Factory>* stmt) {
    body_.push_back(stmt);
  }
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(FunctionLiteral)
 private:
  Identifier<Factory>* name_;
  DeclType type_;
  Identifiers params_;
  Statements body_;
  Scope<Factory> scope_;
  bool strict_;
  std::size_t start_position_;
  std::size_t end_position_;
  UStringPiece source_;
};

template<typename Factory>
class PropertyAccess : public Expression<Factory> {
 public:
  inline bool IsValidLeftHandSide() const { return true; }
  inline Expression<Factory>* target() const { return target_; }
  DECLARE_NODE_TYPE(PropertyAccess)
 protected:
  explicit PropertyAccess(Expression<Factory>* obj)
    : target_(obj) {
  }
  Expression<Factory>* target_;
};

template<typename Factory>
class IdentifierAccess : public PropertyAccess<Factory> {
 public:
  IdentifierAccess(Expression<Factory>* obj,
                   Identifier<Factory>* key)
    : PropertyAccess<Factory>(obj),
      key_(key) {
  }
  inline Identifier<Factory>* key() const { return key_; }
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(IdentifierAccess)
 private:
  Identifier<Factory>* key_;
};

template<typename Factory>
class IndexAccess : public PropertyAccess<Factory> {
 public:
  IndexAccess(Expression<Factory>* obj,
              Expression<Factory>* key)
    : PropertyAccess<Factory>(obj),
      key_(key) {
  }
  inline Expression<Factory>* key() const { return key_; }
  DECLARE_NODE_TYPE(IndexAccess)
  ACCEPT_VISITOR
 private:
  Expression<Factory>* key_;
};

template<typename Factory>
class Call : public Expression<Factory> {
 public:
  typedef typename SpaceVector<Factory, Expression<Factory>*>::type Expressions;
  inline bool IsValidLeftHandSide() const { return true; }
  Call(Expression<Factory>* target,
       Factory* factory)
    : target_(target),
      args_(typename Expressions::allocator_type(factory)) {
  }
  void AddArgument(Expression<Factory>* expr) { args_.push_back(expr); }
  inline Expression<Factory>* target() const { return target_; }
  inline const Expressions& args() const { return args_; }
  DECLARE_NODE_TYPE(Call)
 protected:
  Expression<Factory>* target_;
  Expressions args_;
};

template<typename Factory>
class FunctionCall : public Call<Factory> {
 public:
  FunctionCall(Expression<Factory>* target,
               Factory* factory)
    : Call<Factory>(target, factory) {
  }
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(FunctionCall)
};

template<typename Factory>
class ConstructorCall : public Call<Factory> {
 public:
  ConstructorCall(Expression<Factory>* target,
                  Factory* factory)
    : Call<Factory>(target, factory) {
  }
  ACCEPT_VISITOR
  DECLARE_NODE_TYPE(ConstructorCall)
};

} } }  // namespace iv::core::ast
namespace std {
namespace tr1 {
// template specialization
// for iv::core::Parser::IdentifierWrapper in std::tr1::unordered_map
// allowed in section 17.4.3.1
template<class Factory>
struct hash<iv::core::ast::IdentifierKey<Factory> >
  : public unary_function<iv::core::ast::IdentifierKey<Factory>, std::size_t> {
  std::size_t operator()(const iv::core::ast::IdentifierKey<Factory>& x) const {
    return hash<
        typename iv::core::ast::Identifier<Factory>::value_type>()(x.value());
  }
};
} }  // namespace std::tr1
#undef ACCEPT_VISITOR
#undef DECLARE_NODE_TYPE
#undef DECLARE_NODE_TYPE_BASE
#endif  // _IV_AST_H_
