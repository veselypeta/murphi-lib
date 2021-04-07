#pragma once
#include "models/Expr.h"
#include <string>

namespace murphi {
class ConstDecl {
public:
  ConstDecl(std::string id, Expr *expr) : id(id), expression(expr) {}
  ~ConstDecl() { delete expression; }
  std::string getAsString();

private:
  std::string id;
  Expr *expression;
};
} // namespace murphi
