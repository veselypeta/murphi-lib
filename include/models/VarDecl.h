#pragma once
#include <string>
#include "models/Decl.h"
#include "models/TypeExpr.h"

namespace murphi {
class VarDecl : public IDecl {
 public:
  VarDecl(std::string id, TypeExpr* expr) : id{std::move(id)}, expr{expr} {}
  VarDecl(const VarDecl& rhs) {
    id = rhs.id;
    expr = rhs.expr->clone();
  }
  ~VarDecl() override { delete expr; }
  [[nodiscard]] VarDecl* clone() const override { return new VarDecl(*this); }
  std::string getAsString() override;
  std::string getId() override;

 private:
  std::string id;
  TypeExpr* expr;
};
}  // namespace murphi
