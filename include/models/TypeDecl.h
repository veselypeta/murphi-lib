#pragma once
#include <string>
#include "interfaces/Identifyable.h"
#include "interfaces/Printable.h"
#include "models/TypeExpr.h"

namespace murphi {

//<typedecl> ::=	<ID> : <typeExpr>
class TypeDecl : Printable<TypeDecl>, Identifyable<TypeDecl> {
 public:
  TypeDecl(std::string id, TypeExpr* expr) : id(id), expr(expr) {}
  ~TypeDecl() { delete expr; }
  std::string getAsString();
  std::string getId() { return id; }

 private:
  std::string id;
  TypeExpr* expr;
};

}  // namespace murphi
