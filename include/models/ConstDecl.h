#pragma once
#include <string>
#include "interfaces/Identifyable.h"
#include "interfaces/Printable.h"
#include "models/Expr.h"

namespace murphi {
// <constdecl> ::=	<ID> : <expr>
class ConstDecl : Identifyable<ConstDecl>, Printable<ConstDecl> {
 public:
  ConstDecl(std::string id, Expr* expr) : id(id), expression(expr) {}
  ~ConstDecl() { delete expression; }
  std::string getAsString();
  std::string getId();

 private:
  std::string id;
  Expr* expression;
};
}  // namespace murphi
