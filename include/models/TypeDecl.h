#pragma once
#include <string>
#include "models/Decl.h"
#include "models/TypeExpr.h"

namespace murphi {

//<typedecl> ::=	<ID> : <typeExpr>
class TypeDecl : public IDecl {
 public:
  TypeDecl(std::string id, TypeExpr* expr) : id{std::move(id)}, expr{expr} {}
  TypeDecl(const TypeDecl& rhs) {
    id = rhs.id;
    expr = rhs.expr->clone();
  }
  ~TypeDecl() override { delete expr; }
  [[nodiscard]] TypeDecl* clone() const override { return new TypeDecl(*this); }
  std::string getAsString() override;
  std::string getId() override { return id; }

 private:
  std::string id;
  TypeExpr* expr;
};

}  // namespace murphi
