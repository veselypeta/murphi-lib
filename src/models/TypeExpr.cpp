#include "models/TypeExpr.h"
#include <string>

namespace murphi {
std::string ID::getAsString() {
  return typeId;
}

std::string IntegerSubRange::getAsString(){
  return lhs->getAsString() + " .. " + rhs->getAsString();
}
}  // namespace murphi
