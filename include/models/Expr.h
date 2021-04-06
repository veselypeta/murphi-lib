#pragma once
#include <memory>
#include <string>

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
// Abstract Class Expression
class Expr {
public:
  virtual std::string getAsString() = 0;
  virtual ~Expr(){};
};

class IntExpr : public Expr {
public:
  IntExpr(int value) : exprVal(value) {}
  virtual std::string getAsString();
  ~IntExpr() {}

private:
  int exprVal;
};

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

class ParenthExpr : public Expr {
public:
  ParenthExpr(Expr *ex) : ex(ex) {}
  virtual std::string getAsString();
  ~ParenthExpr() { delete ex; }

private:
  Expr *ex;
};

} // namespace murphi
