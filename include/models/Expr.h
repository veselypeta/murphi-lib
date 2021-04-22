#pragma once
#include "interfaces/Printable.h"
#include <string>
#include <vector>

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
  virtual std::string getAsString() = 0;
  virtual ~Expr(){};
};

/* \( expr \) */
class ParenthExpr : public Expr {
public:
  ParenthExpr(Expr *ex) : ex(ex) {}
  virtual std::string getAsString();
  ~ParenthExpr() { delete ex; }

private:
  Expr *ex;
};

// <designator>
class Designator : public Expr {
public:
  Designator(std::string id) : id{id} {}
  ~Designator() {}
  std::string getAsString();
  void addIndex(std::string fieldId);
  void addIndex(Expr *arrIndex);

private:
  typedef enum { ID, EXPR } identOrExpr;
  class Container {
  public:
    Container(std::string fieldId)
        : fieldId{fieldId}, expr{nullptr}, type{ID} {}
    Container(Expr *expr) : fieldId{""}, expr{expr}, type{EXPR} {}
    ~Container() {
      // TODO - there is a resource leak, not deleting expr
    }
    std::string getAsString() {
      if (type == ID) {
        return "." + fieldId;
      } else {
        return "[" + expr->getAsString() + "]";
      }
    }

  private:
    std::string fieldId;
    Expr *expr;
    identOrExpr type;
  };
  std::string id;
  std::vector<Container> indexes;
};

// <integer-constant>
class IntExpr : public Expr {
public:
  IntExpr(int value) : exprVal(value) {}
  virtual std::string getAsString();
  ~IntExpr() {}

private:
  int exprVal;
};

// <expr> + <expr>
class AddExpr : public Expr {
public:
  AddExpr(Expr *lhs, Expr *rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string getAsString();
  ~AddExpr() {
    delete lhs;
    delete rhs;
  }

private:
  Expr *lhs;
  Expr *rhs;
};

// <expr> - <expr>
class SubExpr : public Expr {
public:
  SubExpr(Expr *lhs, Expr *rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string getAsString();
  ~SubExpr() {
    delete lhs;
    delete rhs;
  }

private:
  Expr *lhs;
  Expr *rhs;
};

// <expr> * <expr>
class MultExpr : public Expr {
public:
  MultExpr(Expr *lhs, Expr *rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string getAsString();
  ~MultExpr() {
    delete lhs;
    delete rhs;
  }

private:
  Expr *lhs;
  Expr *rhs;
};

// <expr> / <expr>
class DivExpr : public Expr {
public:
  DivExpr(Expr *lhs, Expr *rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string getAsString();
  ~DivExpr() {
    delete lhs;
    delete rhs;
  }

private:
  Expr *lhs;
  Expr *rhs;
};

// <expr> % <expr>
class RemExpr : public Expr {
public:
  RemExpr(Expr *lhs, Expr *rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string getAsString();
  ~RemExpr() {
    delete lhs;
    delete rhs;
  }

private:
  Expr *lhs;
  Expr *rhs;
};

// ! <expr>			-- logical negation.
class LogNegExpr : public Expr {
public:
  LogNegExpr(Expr *expr) : expr(expr) {}
  virtual std::string getAsString();
  ~LogNegExpr() { delete expr; }

private:
  Expr *expr;
};

// <expr> | <expr>
class LogDisjExpr : public Expr {
public:
  LogDisjExpr(Expr *lhs, Expr *rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string getAsString();
  ~LogDisjExpr() {
    delete lhs;
    delete rhs;
  }

private:
  Expr *lhs;
  Expr *rhs;
};

// <expr> % <expr>
class LogConjExpr : public Expr {
public:
  LogConjExpr(Expr *lhs, Expr *rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string getAsString();
  ~LogConjExpr() {
    delete lhs;
    delete rhs;
  }

private:
  Expr *lhs;
  Expr *rhs;
};

// <expr> -> <expr>
class LogImplExpr : public Expr {
public:
  LogImplExpr(Expr *lhs, Expr *rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string getAsString();
  ~LogImplExpr() {
    delete lhs;
    delete rhs;
  }

private:
  Expr *lhs;
  Expr *rhs;
};

// <expr> < <expr>
class LTExpr : public Expr {
public:
  LTExpr(Expr *lhs, Expr *rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string getAsString();
  ~LTExpr() {
    delete lhs;
    delete rhs;
  }

private:
  Expr *lhs;
  Expr *rhs;
};

// <expr> <= <expr>
class LTEQExpr : public Expr {
public:
  LTEQExpr(Expr *lhs, Expr *rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string getAsString();
  ~LTEQExpr() {
    delete lhs;
    delete rhs;
  }

private:
  Expr *lhs;
  Expr *rhs;
};

// <expr> > <expr>
class GTExpr : public Expr {
public:
  GTExpr(Expr *lhs, Expr *rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string getAsString();
  ~GTExpr() {
    delete lhs;
    delete rhs;
  }

private:
  Expr *lhs;
  Expr *rhs;
};

// <expr> >= <expr>
class GTEQExpr : public Expr {
public:
  GTEQExpr(Expr *lhs, Expr *rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string getAsString();
  ~GTEQExpr() {
    delete lhs;
    delete rhs;
  }

private:
  Expr *lhs;
  Expr *rhs;
};

// <expr> = <expr>
class EQExpr : public Expr {
public:
  EQExpr(Expr *lhs, Expr *rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string getAsString();
  ~EQExpr() {
    delete lhs;
    delete rhs;
  }

private:
  Expr *lhs;
  Expr *rhs;
};

// <expr> != <expr>
class NEQExpr : public Expr {
public:
  NEQExpr(Expr *lhs, Expr *rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string getAsString();
  ~NEQExpr() {
    delete lhs;
    delete rhs;
  }

private:
  Expr *lhs;
  Expr *rhs;
};

// <expr> ? <expr> : <expr>	-- C-style conditional expression.
class CondExpr : public Expr {
public:
  CondExpr(Expr *condExpr, Expr *thenExpr, Expr *elseExpr)
      : condExpr(condExpr), thenExpr(thenExpr), elseExpr(elseExpr) {}
  ~CondExpr() {
    delete condExpr;
    delete thenExpr;
    delete elseExpr;
  }
  virtual std::string getAsString();

private:
  Expr *condExpr;
  Expr *thenExpr;
  Expr *elseExpr;
};

// <expr> : | ISUNDEFINED '(' designator ')';
class IsUndefExpr : public Expr {
public:
  IsUndefExpr(Designator *des) : des{des} {}
  ~IsUndefExpr() { delete des; }
  virtual std::string getAsString();

private:
  Designator *des;
};

// <expr> : | ISMEMBER '(' designator ',' typeExpr ')' ;
class IsMemberExpr : public Expr {
public:
  IsMemberExpr(Designator *des, TypeExpr *tyexpr) : des{des}, tyexpr{tyexpr} {}
  ~IsMemberExpr();
  virtual std::string getAsString();

private:
  Designator *des;
  TypeExpr *tyexpr;
};

class MultiSetCountExpr : public Expr {
public:
  MultiSetCountExpr(std::string var, Expr *expr) : var{var}, expr{expr} {}
  ~MultiSetCountExpr() {
    delete expr;
  }
  virtual std::string getAsString();

private:
  std::string var;
  Expr *expr;
};

} // namespace murphi
