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
  std::string getAsString() override = 0;
  [[nodiscard]] virtual TypeExpr* clone() const = 0;
  virtual ~TypeExpr() = default;
};

// <ID>		-- a previously defined type.
class ID : public TypeExpr {
 public:
  explicit ID(std::string typeId) : typeId{std::move(typeId)} {}
  ID(const ID& rhs) = default;
  ~ID() override = default;
  [[nodiscard]] ID* clone() const override { return new ID(*this); }
  std::string getAsString() override;

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
  ~IntegerSubRange() override {
    delete lhs;
    delete rhs;
  }
  [[nodiscard]] IntegerSubRange* clone() const override { return new IntegerSubRange(*this); }
  std::string getAsString() override;

 private:
  Expr* lhs;
  Expr* rhs;
};

// <typeExpr> ::=	enum \{ <ID> {, <ID> } \} -- enumeration.
class Enum : public TypeExpr {
 public:
  Enum() = default;
  explicit Enum(std::vector<std::string> es) : es{std::move(es)} {}
  Enum(const Enum& rhs) = default;
  ~Enum() override = default;
  [[nodiscard]] Enum* clone() const override { return new Enum(*this); }
  std::string getAsString() override;
  void addEnum(std::string e);

 private:
  std::vector<std::string> es;
};

// <typeExpr> ::=	record { <vardecl> } end
class Record : public TypeExpr {
 public:
  Record() = default;
  Record(const Record& rhs);
  ~Record() override { body.clear(); }
  [[nodiscard]] Record* clone() const override { return new Record(*this); }
  std::string getAsString() override;
  void addVarDecl(VarDecl* vd);

 private:
  std::vector<VarDecl*> body;
};

// scalarsettype   : SCALARSET "(" expr ")"
class ScalarSet : public TypeExpr {
 public:
  explicit ScalarSet(Expr* expr) : expr{expr} {}
  ScalarSet(const ScalarSet& rhs) { expr = rhs.expr->clone(); }
  ~ScalarSet() override { delete expr; }
  [[nodiscard]] ScalarSet* clone() const override { return new ScalarSet(*this); }
  std::string getAsString() override;

 private:
  Expr* expr;
};

// <typeExpr> ::= uniontype	/ scalarset /
class Union : public TypeExpr {
 public:
  // TODO - make this a prameter list
  Union(std::string elem, std::string elem2) {
    elems.push_back(std::move(elem));
    elems.push_back(std::move(elem2));
  }
  Union(const Union& rhs) = default;
  ~Union() override = default;

  [[nodiscard]] Union* clone() const override { return new Union(*this); }
  std::string getAsString() override;

  void addElem(std::string elem) { return elems.push_back(std::move(elem)); }

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
  ~MultiSet() override {
    delete expr;
    delete tyExpr;
  };
  [[nodiscard]] MultiSet* clone() const override { return new MultiSet(*this); }
  std::string getAsString() override;

 private:
  Expr* expr;
  TypeExpr* tyExpr;
};

}  // namespace murphi
