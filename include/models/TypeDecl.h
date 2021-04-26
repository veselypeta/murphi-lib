#pragma once
#include "models/Decl.h"
#include "models/TypeExpr.h"
#include <string>

namespace murphi {

//<typedecl> ::=	<ID> : <typeExpr>
class TypeDecl : public IDecl {
public:
  TypeDecl(std::string id, TypeExpr *expr) : id{id}, expr{expr} {}
  TypeDecl(const TypeDecl &rhs) {
    id = rhs.id;
    expr = rhs.expr->clone();
  }
  ~TypeDecl() { delete expr; }
  virtual TypeDecl *clone() const { return new TypeDecl(*this); }
  virtual std::string getAsString();
  virtual std::string getId() { return id; }

private:
  std::string id;
  TypeExpr *expr;
};

} // namespace murphi
