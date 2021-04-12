#pragma once
#include <string>
#include "models/Decl.h"
#include "models/Expr.h"

namespace murphi {
// <constdecl> ::=	<ID> : <expr>
class ConstDecl : public IDecl {
 public:
  ConstDecl(std::string id, Expr* expr) : id{id}, expression{expr} {}
  ~ConstDecl() { delete expression; }
  std::string getAsString();
  std::string getId();

 private:
  std::string id;
  Expr* expression;
};
}  // namespace murphi
