#include "murphi.h"
#include "models/ConstDecl.h"
#include "models/TypeDecl.h"
#include "models/TypeExpr.h"
#include "models/VarDecl.h"
#include <iostream>
#include <sstream>
#include <string>

namespace murphi {

void Module::addConstDecl(std::string id, murphi::Expr *expr) {
  murphi::ConstDecl *cd = new murphi::ConstDecl(id, expr);
  decls.addDecl(cd);
}

void Module::addTypeDecl(std::string id, TypeExpr *expr) {
  murphi::TypeDecl *tDecl = new murphi::TypeDecl(id, expr);
  decls.addDecl(tDecl);
}

void Module::addVarDecl(std::string id, TypeExpr *expr) {
  murphi::VarDecl *vdecl = new murphi::VarDecl(id, expr);
  decls.addDecl(vdecl);
}

bool Module::isVaidReference(std::string id) {
  return decls.isValidReference(id);
}

std::string Module::getAsString() { return decls.getAsString(); }

void murphi::Module::dump() { std::cout << getAsString() << std::endl; }

} // namespace murphi
