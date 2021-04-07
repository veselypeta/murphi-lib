#include "models/Decl.h"
#include "models/ConstDecl.h"

namespace murphi {
std::string Decl::getAsString() {
  // print the const decls
  std::string s;
  s += "const \n";
  for (ConstDecl* cd : constDecls) {
    s += "\t" + cd->getAsString() + "\n";
  }

  // TODO - print all other decls
  return s;
}
}  // namespace murphi
