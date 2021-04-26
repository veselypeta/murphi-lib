#pragma once
#include "models/Decl.h"
#include "models/Expr.h"
#include <string>

namespace murphi {
// <constdecl> ::=	<ID> : <expr>
class ConstDecl : public IDecl {
public:
  ConstDecl(std::string id, Expr *expr) : id{id}, expression{expr} {}
  ConstDecl(const ConstDecl &rhs) {
    id = rhs.id;
    expression = rhs.expression->clone();
  }
  ~ConstDecl() { delete expression; }
  virtual ConstDecl *clone() const { return new ConstDecl(*this); }
  virtual std::string getAsString();
  virtual std::string getId();

private:
  std::string id;
  Expr *expression;
};
} // namespace murphi
