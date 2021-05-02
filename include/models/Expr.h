#pragma once
#include <string>
#include <utility>
#include <vector>
#include "interfaces/Printable.h"

/*
 -- Grammar for expressions
<expr> :=  \( expr \)
         | <designator>
         | <integer-constant>
         | <ID> \( <actuals> \)		-- a function call.
         | forall <quantifier>
           do <expr> endforall		-- universal quantification.
         | exists <quantifier>
           do <expr> endexists		-- existential quantification.
         | <expr> + <expr>
         | <expr> - <expr>
         | <expr> * <expr>		-- multiplication.
         | <expr> / <expr>		-- integer division.
         | <expr> % <expr>		-- remainder.
         | ! <expr>			-- logical negation.
         | <expr> | <expr>		-- logical disjunction.
         | <expr> & <expr>		-- logical conjunction.
         | <expr> -> <expr>		-- logical implication.
         | <expr> < <expr>
         | <expr> <= <expr>
         | <expr> > <expr>
         | <expr> >= <expr>
         | <expr> = <expr>
         | <expr> != <expr>
         | <expr> ? <expr> : <expr>	-- C-style conditional expression.

*/
namespace murphi {
class TypeExpr;
// Abstract Class Expression
class Expr : public Printable<Expr> {
 public:
  std::string getAsString() override = 0;
  [[nodiscard]] virtual Expr* clone() const = 0;
  virtual ~Expr() = default;
  ;
};

/* \( expr \) */
class ParenthExpr : public Expr {
 public:
  explicit ParenthExpr(Expr* ex) : ex(ex) {}
  ParenthExpr(const ParenthExpr& rhs) { ex = rhs.ex->clone(); }
  std::string getAsString() override;
  // clone calls the actual copy constructor
  [[nodiscard]] ParenthExpr* clone() const override {
    return new ParenthExpr(*this);
  };
  ~ParenthExpr() override { delete ex; }

 private:
  Expr* ex;
};

// <designator>
class Designator : public Expr {
 public:
  explicit Designator(std::string id) : id{std::move(id)} {}
  Designator(const Designator& rhs) = default;
  [[nodiscard]] Designator* clone() const override {
    return new Designator(*this);
  }
  ~Designator() override = default;
  std::string getAsString() override;
  void addIndex(std::string fieldId);
  void addIndex(Expr* arrIndex);

 private:
  typedef enum { ID, EXPR } identOrExpr;
  class Container {
   public:
    explicit Container(std::string fieldId)
        : fieldId{fieldId}, expr{nullptr}, type{ID} {}
    explicit Container(Expr* expr) : expr{expr}, type{EXPR} {}
    Container(const Container& rhs) {
      if (rhs.expr != nullptr) {
        expr = rhs.expr->clone();
      } else {
        expr = nullptr;
      }
      fieldId = rhs.fieldId;
      type = rhs.type;
    };
    ~Container() { delete expr; }
    std::string getAsString() {
      if (type == ID) {
        return "." + fieldId;
      } else {
        return "[" + expr->getAsString() + "]";
      }
    }

   private:
    std::string fieldId;
    Expr* expr;
    identOrExpr type;
  };
  std::string id;
  std::vector<Container> indexes;
};

// <integer-constant>
class IntExpr : public Expr {
 public:
  explicit IntExpr(int value) : exprVal(value) {}
  IntExpr(const IntExpr& rhs) = default;
  [[nodiscard]] IntExpr* clone() const override { return new IntExpr(*this); }
  std::string getAsString() override;
  ~IntExpr() override = default;

 private:
  int exprVal;
};

// <expr> + <expr>
class AddExpr : public Expr {
 public:
  AddExpr(Expr* lhs, Expr* rhs) : lhs(lhs), rhs(rhs) {}
  AddExpr(const AddExpr& in) {
    lhs = in.lhs->clone();
    rhs = in.rhs->clone();
  }
  [[nodiscard]] AddExpr* clone() const override { return new AddExpr(*this); }
  std::string getAsString() override;
  ~AddExpr() override {
    delete lhs;
    delete rhs;
  }

 private:
  Expr* lhs;
  Expr* rhs;
};

// <expr> - <expr>
class SubExpr : public Expr {
 public:
  SubExpr(Expr* lhs, Expr* rhs) : lhs(lhs), rhs(rhs) {}
  SubExpr(const SubExpr& in) {
    lhs = in.lhs->clone();
    rhs = in.rhs->clone();
  }
  [[nodiscard]] SubExpr* clone() const override { return new SubExpr(*this); }
  std::string getAsString() override;
  ~SubExpr() override {
    delete lhs;
    delete rhs;
  }

 private:
  Expr* lhs;
  Expr* rhs;
};

// <expr> * <expr>
class MultExpr : public Expr {
 public:
  MultExpr(Expr* lhs, Expr* rhs) : lhs(lhs), rhs(rhs) {}
  MultExpr(const MultExpr& in) {
    lhs = in.lhs->clone();
    rhs = in.rhs->clone();
  }
  [[nodiscard]] MultExpr* clone() const override { return new MultExpr(*this); }
  std::string getAsString() override;
  ~MultExpr() override {
    delete lhs;
    delete rhs;
  }

 private:
  Expr* lhs;
  Expr* rhs;
};

// <expr> / <expr>
class DivExpr : public Expr {
 public:
  DivExpr(Expr* lhs, Expr* rhs) : lhs(lhs), rhs(rhs) {}
  DivExpr(const DivExpr& in) {
    lhs = in.lhs->clone();
    rhs = in.rhs->clone();
  }
  [[nodiscard]] DivExpr* clone() const override { return new DivExpr(*this); }
  std::string getAsString() override;
  ~DivExpr() override {
    delete lhs;
    delete rhs;
  }

 private:
  Expr* lhs;
  Expr* rhs;
};

// <expr> % <expr>
class RemExpr : public Expr {
 public:
  RemExpr(Expr* lhs, Expr* rhs) : lhs(lhs), rhs(rhs) {}
  RemExpr(const RemExpr& in) {
    lhs = in.lhs->clone();
    rhs = in.rhs->clone();
  }
  [[nodiscard]] RemExpr* clone() const override { return new RemExpr(*this); }
  std::string getAsString() override;
  ~RemExpr() override {
    delete lhs;
    delete rhs;
  }

 private:
  Expr* lhs;
  Expr* rhs;
};

// ! <expr>			-- logical negation.
class LogNegExpr : public Expr {
 public:
  explicit LogNegExpr(Expr* expr) : expr(expr) {}
  LogNegExpr(const LogNegExpr& rhs) { expr = rhs.clone(); }
  ~LogNegExpr() override { delete expr; }
  [[nodiscard]] LogNegExpr* clone() const override {
    return new LogNegExpr(*this);
  }
  std::string getAsString() override;

 private:
  Expr* expr;
};

// <expr> | <expr>
class LogDisjExpr : public Expr {
 public:
  LogDisjExpr(Expr* lhs, Expr* rhs) : lhs(lhs), rhs(rhs) {}
  LogDisjExpr(const LogDisjExpr& in) {
    lhs = in.lhs->clone();
    rhs = in.rhs->clone();
  }
  [[nodiscard]] LogDisjExpr* clone() const override {
    return new LogDisjExpr(*this);
  }
  std::string getAsString() override;
  ~LogDisjExpr() override {
    delete lhs;
    delete rhs;
  }

 private:
  Expr* lhs;
  Expr* rhs;
};

// <expr> % <expr>
class LogConjExpr : public Expr {
 public:
  LogConjExpr(Expr* lhs, Expr* rhs) : lhs(lhs), rhs(rhs) {}
  LogConjExpr(const LogConjExpr& in) {
    lhs = in.lhs->clone();
    rhs = in.rhs->clone();
  }
  [[nodiscard]] LogConjExpr* clone() const override {
    return new LogConjExpr(*this);
  }
  std::string getAsString() override;
  ~LogConjExpr() override {
    delete lhs;
    delete rhs;
  }

 private:
  Expr* lhs;
  Expr* rhs;
};

// <expr> -> <expr>
class LogImplExpr : public Expr {
 public:
  LogImplExpr(Expr* lhs, Expr* rhs) : lhs(lhs), rhs(rhs) {}
  LogImplExpr(const LogImplExpr& in) {
    lhs = in.lhs->clone();
    rhs = in.rhs->clone();
  }
  [[nodiscard]] LogImplExpr* clone() const override {
    return new LogImplExpr(*this);
  }
  std::string getAsString() override;
  ~LogImplExpr() override {
    delete lhs;
    delete rhs;
  }

 private:
  Expr* lhs;
  Expr* rhs;
};

// <expr> < <expr>
class LTExpr : public Expr {
 public:
  LTExpr(Expr* lhs, Expr* rhs) : lhs(lhs), rhs(rhs) {}
  LTExpr(const LTExpr& in) {
    lhs = in.lhs->clone();
    rhs = in.rhs->clone();
  }
  [[nodiscard]] LTExpr* clone() const override { return new LTExpr(*this); }
  std::string getAsString() override;
  ~LTExpr() override {
    delete lhs;
    delete rhs;
  }

 private:
  Expr* lhs;
  Expr* rhs;
};

// <expr> <= <expr>
class LTEQExpr : public Expr {
 public:
  LTEQExpr(Expr* lhs, Expr* rhs) : lhs(lhs), rhs(rhs) {}
  LTEQExpr(const LTEQExpr& in) {
    lhs = in.lhs->clone();
    rhs = in.rhs->clone();
  }
  [[nodiscard]] LTEQExpr* clone() const override { return new LTEQExpr(*this); }
  std::string getAsString() override;
  ~LTEQExpr() override {
    delete lhs;
    delete rhs;
  }

 private:
  Expr* lhs;
  Expr* rhs;
};

// <expr> > <expr>
class GTExpr : public Expr {
 public:
  GTExpr(Expr* lhs, Expr* rhs) : lhs(lhs), rhs(rhs) {}
  GTExpr(const GTExpr& in) {
    lhs = in.lhs->clone();
    rhs = in.rhs->clone();
  }
  [[nodiscard]] GTExpr* clone() const override { return new GTExpr(*this); }
  std::string getAsString() override;
  ~GTExpr() override {
    delete lhs;
    delete rhs;
  }

 private:
  Expr* lhs;
  Expr* rhs;
};

// <expr> >= <expr>
class GTEQExpr : public Expr {
 public:
  GTEQExpr(Expr* lhs, Expr* rhs) : lhs(lhs), rhs(rhs) {}
  GTEQExpr(const GTEQExpr& in) {
    lhs = in.lhs->clone();
    rhs = in.rhs->clone();
  }
  [[nodiscard]] GTEQExpr* clone() const override { return new GTEQExpr(*this); }
  std::string getAsString() override;
  ~GTEQExpr() override {
    delete lhs;
    delete rhs;
  }

 private:
  Expr* lhs;
  Expr* rhs;
};

// <expr> = <expr>
class EQExpr : public Expr {
 public:
  EQExpr(Expr* lhs, Expr* rhs) : lhs(lhs), rhs(rhs) {}
  EQExpr(const EQExpr& in) {
    lhs = in.lhs->clone();
    rhs = in.rhs->clone();
  }
  [[nodiscard]] EQExpr* clone() const override { return new EQExpr(*this); }
  std::string getAsString() override;
  ~EQExpr() override {
    delete lhs;
    delete rhs;
  }

 private:
  Expr* lhs;
  Expr* rhs;
};

// <expr> != <expr>
class NEQExpr : public Expr {
 public:
  NEQExpr(Expr* lhs, Expr* rhs) : lhs(lhs), rhs(rhs) {}
  NEQExpr(const NEQExpr& in) {
    lhs = in.lhs->clone();
    rhs = in.rhs->clone();
  }
  [[nodiscard]] NEQExpr* clone() const override { return new NEQExpr(*this); }
  std::string getAsString() override;
  ~NEQExpr() override {
    delete lhs;
    delete rhs;
  }

 private:
  Expr* lhs;
  Expr* rhs;
};

// <expr> ? <expr> : <expr>	-- C-style conditional expression.
class CondExpr : public Expr {
 public:
  CondExpr(Expr* condExpr, Expr* thenExpr, Expr* elseExpr)
      : condExpr(condExpr), thenExpr(thenExpr), elseExpr(elseExpr) {}

  CondExpr(const CondExpr& rhs) {
    condExpr = rhs.condExpr->clone();
    thenExpr = rhs.thenExpr->clone();
    elseExpr = rhs.elseExpr->clone();
  }

  [[nodiscard]] CondExpr* clone() const override { return new CondExpr(*this); }
  ~CondExpr() override {
    delete condExpr;
    delete thenExpr;
    delete elseExpr;
  }
  std::string getAsString() override;

 private:
  Expr* condExpr;
  Expr* thenExpr;
  Expr* elseExpr;
};

// <expr> : | ISUNDEFINED '(' designator ')';
class IsUndefExpr : public Expr {
 public:
  explicit IsUndefExpr(Designator* des) : des{des} {}
  IsUndefExpr(const IsUndefExpr& rhs) { des = rhs.des->clone(); }
  ~IsUndefExpr() override { delete des; }
  [[nodiscard]] IsUndefExpr* clone() const override {
    return new IsUndefExpr(*this);
  }
  std::string getAsString() override;

 private:
  Designator* des;
};

// <expr> : | ISMEMBER '(' designator ',' typeExpr ')' ;
class IsMemberExpr : public Expr {
 public:
  IsMemberExpr(Designator* des, TypeExpr* tyexpr) : des{des}, tyexpr{tyexpr} {}
  IsMemberExpr(const IsMemberExpr& rhs) {
    des = rhs.des->clone();
    // TODO - TypeExpr need to be coppied too
    // tyexpr = rhs.tyexpr->clone();
  }
  [[nodiscard]] IsMemberExpr* clone() const override {
    return new IsMemberExpr(*this);
  }
  ~IsMemberExpr() override;
  std::string getAsString() override;

 private:
  Designator* des;
  TypeExpr* tyexpr{};
};

class MultiSetCountExpr : public Expr {
 public:
  MultiSetCountExpr(std::string var, Expr* expr)
      : var{std::move(var)}, expr{expr} {}
  MultiSetCountExpr(const MultiSetCountExpr& rhs) {
    var = rhs.var;
    expr = rhs.expr->clone();
  }
  [[nodiscard]] MultiSetCountExpr* clone() const override {
    return new MultiSetCountExpr(*this);
  }
  ~MultiSetCountExpr() override { delete expr; }
  std::string getAsString() override;

 private:
  std::string var;
  Expr* expr;
};

}  // namespace murphi
