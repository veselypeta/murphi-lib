#include "models/ConstDecl.h"
#include <string>
#include "models/Decl.h"

std::string murphi::ConstDecl::getAsString() {
  return id + " : " + expression->getAsString() + ";";
}

std::string murphi::ConstDecl::getId() {
  return id;
}
