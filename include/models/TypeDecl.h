#pragma once
#include <string>
#include "models/Decl.h"
#include "models/TypeExpr.h"

namespace murphi {

//<typedecl> ::=	<ID> : <typeExpr>
class TypeDecl : public IDecl {
 public:
  TypeDecl(std::string id, TypeExpr* expr) : id{id}, expr{expr} {}
  ~TypeDecl() { delete expr; }
  std::string getAsString();
  std::string getId() { return id; }

 private:
  std::string id;
  TypeExpr* expr;
};

}  // namespace murphi
