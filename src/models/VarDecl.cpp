#include "models/VarDecl.h"
#include <string>
namespace murphi {
std::string VarDecl::getAsString() {
  return getId() + " : " + expr->getAsString() + ";";
}

std::string VarDecl::getId() {
  return id;
}
}  // namespace murphi
