#pragma once
#include <string>
#include "interfaces/Identifyable.h"
#include "interfaces/Printable.h"
#include "models/TypeExpr.h"

namespace murphi {
class VarDecl : Printable<VarDecl>, Identifyable<VarDecl> {
 public:
  VarDecl(std::string id, TypeExpr* expr) : id(id), expr(expr) {}
  ~VarDecl() { delete expr; }
  std::string getAsString();
  std::string getId();

 private:
  std::string id;
  TypeExpr* expr;
};
}  // namespace murphi
