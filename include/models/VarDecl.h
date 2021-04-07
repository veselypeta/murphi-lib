#pragma once
#include "interfaces/Identifyable.h"
#include "interfaces/Printable.h"
#include "models/TypeExpr.h"
#include <string>

namespace murphi {
class VarDecl : public Printable<VarDecl>, public Identifyable<VarDecl> {
public:
  VarDecl(std::string id, TypeExpr *expr) : id(id), expr{expr} {}
  ~VarDecl() { delete expr; }
  std::string getAsString();
  std::string getId();

private:
  std::string id;
  TypeExpr *expr;
};
} // namespace murphi
