#pragma once
#include "models/Decl.h"
#include "models/TypeExpr.h"
#include <string>

namespace murphi {
class VarDecl : public IDecl {
public:
  VarDecl(std::string id, TypeExpr *expr) : id{id}, expr{expr} {}
  VarDecl(const VarDecl &rhs) {
    id = rhs.id;
    expr = rhs.expr->clone();
  }
  ~VarDecl() { delete expr; }
  virtual VarDecl *clone() const { return new VarDecl(*this); }
  virtual std::string getAsString();
  virtual std::string getId();

private:
  std::string id;
  TypeExpr *expr;
};
} // namespace murphi
