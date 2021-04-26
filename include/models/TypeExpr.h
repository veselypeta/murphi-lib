#pragma once
#include <cstdarg>
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
    <typeExpr> ::= scalarsettype // scalarset //
    <typeExpr> ::= uniontype	/ scalarset /
*/

class TypeExpr : public Printable<TypeExpr> {
 public:
  virtual std::string getAsString() = 0;
  virtual TypeExpr* clone() const = 0;
  virtual ~TypeExpr() {}
};

// <ID>		-- a previously defined type.
class ID : public TypeExpr {
 public:
  ID(std::string typeId) : typeId{typeId} {}
  ID(const ID& rhs) = default;
  ~ID() = default;
  virtual ID* clone() const { return new ID(*this); }
  virtual std::string getAsString();

 private:
  std::string typeId;
};

// <expr> .. <expr>	-- Integer subrange.
class IntegerSubRange : public TypeExpr {
 public:
  IntegerSubRange(Expr* lhs, Expr* rhs) : lhs{lhs}, rhs{rhs} {}
  IntegerSubRange(const IntegerSubRange& in) {
    lhs = in.lhs->clone();
    rhs = in.rhs->clone();
  }
  ~IntegerSubRange() {
    delete lhs;
    delete rhs;
  }
  virtual IntegerSubRange* clone() const { return new IntegerSubRange(*this); }
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
  Enum(const Enum& rhs) = default;
  ~Enum() = default;
  virtual Enum* clone() const { return new Enum(*this); }
  virtual std::string getAsString();
  void addEnum(std::string e);

 private:
  std::vector<std::string> es;
};

// <typeExpr> ::=	record { <vardecl> } end
class Record : public TypeExpr {
 public:
  Record() {}
  Record(const Record& rhs);
  ~Record() { body.clear(); }
  virtual Record* clone() const { return new Record(*this); }
  virtual std::string getAsString();
  void addVarDecl(VarDecl* vd);

 private:
  std::vector<VarDecl*> body;
};

// scalarsettype   : SCALARSET "(" expr ")"
class ScalarSet : public TypeExpr {
 public:
  ScalarSet(Expr* expr) : expr{expr} {}
  ScalarSet(const ScalarSet& rhs) { expr = rhs.expr->clone(); }
  ~ScalarSet() { delete expr; }
  virtual ScalarSet* clone() const { return new ScalarSet(*this); }
  virtual std::string getAsString();

 private:
  Expr* expr;
};

// <typeExpr> ::= uniontype	/ scalarset /
class Union : public TypeExpr {
 public:
  // TODO - make this a prameter list
  Union(std::string elem, std::string elem2) {
    elems.push_back(elem);
    elems.push_back(elem2);
  }
  Union(const Union& rhs) = default;
  ~Union() = default;

  virtual Union* clone() const { return new Union(*this); }
  virtual std::string getAsString();

  void addElem(std::string elem) { return elems.push_back(elem); }

 private:
  std::vector<std::string> elems;
};

// multisettype	: MULTISET "[" expr "]" OF typeExpr
class MultiSet : public TypeExpr {
 public:
  MultiSet(Expr* expr, TypeExpr* tyExpr) : expr{expr}, tyExpr{tyExpr} {}
  MultiSet(const MultiSet& rhs) {
    expr = rhs.expr->clone();
    tyExpr = rhs.tyExpr->clone();
  }
  ~MultiSet() {
    delete expr;
    delete tyExpr;
  };
  virtual MultiSet* clone() const { return new MultiSet(*this); }
  virtual std::string getAsString();

 private:
  Expr* expr;
  TypeExpr* tyExpr;
};

}  // namespace murphi
