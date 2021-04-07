#include "models/ConstDecl.h"
#include "models/Decl.h"
#include <string>

std::string murphi::ConstDecl::getAsString() {
  return id + " : " + expression->getAsString() + ";";
}

std::string murphi::ConstDecl::getId() { return id; }
