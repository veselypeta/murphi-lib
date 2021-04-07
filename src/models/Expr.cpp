#include "models/Expr.h"
#include <string>

namespace murphi {

std::string IntExpr::getAsString() {
  return std::to_string(exprVal);
}

std::string AddExpr::getAsString() {
  return lhs->getAsString() + " + " + rhs->getAsString();
}

std::string ParenthExpr::getAsString() {
  return "(" + ex->getAsString() + ")";
}
}  // namespace murphi
