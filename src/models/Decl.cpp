#include "models/Decl.h"
#include "models/ConstDecl.h"
#include "models/TypeDecl.h"

namespace murphi {
std::string Decl::getAsString() {
  // print the const decls
  std::string s;
  s += "const \n";
  for (ConstDecl* cd : constDecls) {
    s += "\t" + cd->getAsString() + "\n";
  }

  // print the type decls
  s += "type \n";
  for (TypeDecl* td : typeDecls) {
    s += "\t" + td->getAsString() + "\n";
  }

  // TODO - print all other decls
  return s;
}

bool Decl::isValidReference(std::string id) {
  // Check the consts
  for (ConstDecl* cd : constDecls) {
    if (cd->getId() == id) {
      return true;
    }
  }

  // Check the TypeDefs
  for (TypeDecl* td : typeDecls) {
    if (td->getId() == id) {
      return true;
    }
  }
  return false;
}
}  // namespace murphi
