#pragma once
#include "interfaces/Printable.h"
#include "models/Expr.h"
#include <cstdarg>
#include <string>
#include <vector>

namespace murphi {
class VarDecl;
/*
    <typeExpr> ::=	<ID>		-- a previously defined type.
    <typeExpr> ::=	<expr> .. <expr>	-- Integer subrange.
    <typeExpr> ::=	enum \{ <ID> {, <ID> } \} -- enumeration.
    <typeExpr> ::=	record { <vardecl> } end
    <typeExpr> ::=	array \[ <typeExpr> \] of <typeExpr>
    <typeExpr> ::= scalarsettype // scalarset //
    <typeExpr> ::= uniontype	/ scalarset /
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
  IntegerSubRange(Expr *lhs, Expr *rhs) : lhs{lhs}, rhs{rhs} {}
  ~IntegerSubRange() {
    delete lhs;
    delete rhs;
  }
  virtual std::string getAsString();

private:
  Expr *lhs;
  Expr *rhs;
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
  void addVarDecl(VarDecl *vd);

private:
  std::vector<VarDecl *> body;
};

// scalarsettype   : SCALARSET "(" expr ")"
class ScalarSet : public TypeExpr {
public:
  ScalarSet(Expr *expr) : expr{expr} {}
  ~ScalarSet() { delete expr; }

  virtual std::string getAsString();

private:
  Expr *expr;
};

// <typeExpr> ::= uniontype	/ scalarset /
class Union : public TypeExpr {

public:
  // TODO - make this a prameter list
  Union(std::string elem, std::string elem2) {
    elems.push_back(elem);
    elems.push_back(elem2);
  }

  void addElem(std::string elem) { return elems.push_back(elem); }

  virtual std::string getAsString();

private:
  std::vector<std::string> elems;
};

// multisettype	: MULTISET "[" expr "]" OF typeExpr
class MultiSet : public TypeExpr {
public:
  MultiSet(Expr *expr, TypeExpr *tyExpr) : expr{expr}, tyExpr{tyExpr} {}
  ~MultiSet(){
    delete expr;
    delete tyExpr;
  };
  virtual std::string getAsString();

private:
  Expr *expr;
  TypeExpr *tyExpr;
};

} // namespace murphi
