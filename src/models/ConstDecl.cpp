#include "models/ConstDecl.h"
#include <string>
#include "models/Decl.h"

namespace murphi {

std::string ConstDecl::getAsString() {
  return id + " : " + expression->getAsString();
}

std::string ConstDecl::getId() {
  return id;
}
}  // namespace murphi
