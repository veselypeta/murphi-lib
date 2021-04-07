#include "murphi.h"
#include <iostream>
#include <sstream>
#include <string>
#include "models/ConstDecl.h"

namespace murphi {

void Module::addConstDecl(std::string id, murphi::Expr* expr) {
  // TODO -- add a constant to the module
  murphi::ConstDecl* constDecl = new murphi::ConstDecl(id, expr);
  decls.addConstDecl(constDecl);
}

std::string Module::getAsString() {
  return decls.getAsString();
}

void murphi::Module::dump() {
  std::cout << getAsString() << std::endl;
}

}  // namespace murphi
