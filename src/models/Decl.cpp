#include "models/Decl.h"
#include "models/ConstDecl.h"
#include "models/TypeDecl.h"
#include <string>

namespace murphi {
std::string Decls::getAsString() {
  std::string s;
  return s;
}
bool Decls::isValidReference(std::string id) {
  for (IDecl *d : decls) {
    if (d->getId() == id) {
      return true;
    }
  }
  return false;
}
} // namespace murphi
