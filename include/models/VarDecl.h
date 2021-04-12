#pragma once
#include <string>
#include "models/Decl.h"
#include "models/TypeExpr.h"

namespace murphi {
class VarDecl : public IDecl {
 public:
  VarDecl(std::string id, TypeExpr* expr) : id{id}, expr{expr} {}
  ~VarDecl() { delete expr; }
  std::string getAsString();
  std::string getId();

 private:
  std::string id;
  TypeExpr* expr;
};
}  // namespace murphi
