#pragma once
#include <string>
#include "interfaces/Printable.h"

namespace murphi {
/*
    <typeExpr> ::=	<ID>		-- a previously defined type.
    <typeExpr> ::=	<expr> .. <expr>	-- Integer subrange.
    <typeExpr> ::=	enum \{ <ID> {, <ID> } \} -- enumeration.
    <typeExpr> ::=	record { <vardecl> } end
    <typeExpr> ::=	array \[ <typeExpr> \] of <typeExpr>
    ... multiset & scalarset
*/
class TypeExpr : Printable<TypeExpr> {
 public:
  virtual std::string getAsString() = 0;
  virtual ~TypeExpr() {}
};

class IdTypeExpr : public TypeExpr {
 public:
  IdTypeExpr(std::string typeId) : typeId(typeId) {}
  std::string getAsString();

 private:
  std::string typeId;
};
}  // namespace murphi
