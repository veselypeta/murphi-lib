#include "models/ConstDecl.h"
#include "models/Decl.h"
#include <string>

namespace murphi {

std::string ConstDecl::getAsString() {
  return id + " : " + expression->getAsString() + ";";
}

std::string ConstDecl::getId() { return id; }
} // namespace murphi
