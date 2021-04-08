#pragma once
#include <string>
#include <vector>
#include "interfaces/Printable.h"
#include "models/Expr.h"

namespace murphi {
class VarDecl;
/*
    <typeExpr> ::=	<ID>		-- a previously defined type.
    <typeExpr> ::=	<expr> .. <expr>	-- Integer subrange.
    <typeExpr> ::=	enum \{ <ID> {, <ID> } \} -- enumeration.
    <typeExpr> ::=	record { <vardecl> } end
    <typeExpr> ::=	array \[ <typeExpr> \] of <typeExpr>
    ... multiset & scalarset
*/
class TypeExpr : public Printable<TypeExpr> {
 public:
  virtual std::string getAsString() = 0;
  virtual ~TypeExpr() {}
};

// <ID>		-- a previously defined type.
class ID : public TypeExpr {
 public:
  ID(std::string typeId) : typeId{typeId} {}
  virtual std::string getAsString();

 private:
  std::string typeId;
};

// <expr> .. <expr>	-- Integer subrange.
class IntegerSubRange : public TypeExpr {
 public:
  IntegerSubRange(Expr* lhs, Expr* rhs) : lhs{lhs}, rhs{rhs} {}
  ~IntegerSubRange() {
    delete lhs;
    delete rhs;
  }
  virtual std::string getAsString();

 private:
  Expr* lhs;
  Expr* rhs;
};

// <typeExpr> ::=	enum \{ <ID> {, <ID> } \} -- enumeration.
class Enum : public TypeExpr {
 public:
  Enum() {}
  Enum(std::vector<std::string> es) : es{es} {}
  ~Enum() { es.clear(); }

  virtual std::string getAsString();
  void addEnum(std::string e);

 private:
  std::vector<std::string> es;
};

// <typeExpr> ::=	record { <vardecl> } end
class Record : public TypeExpr {
 public:
  Record() {}
  ~Record() { body.clear(); }

  virtual std::string getAsString();
  void addVarDecl(VarDecl* vd);

 private:
  std::vector<VarDecl*> body;
};

}  // namespace murphi
