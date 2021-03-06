#include "models/Decl.h"
#include <string>
#include "models/ConstDecl.h"
#include "models/TypeDecl.h"
#include "models/VarDecl.h"
#include "utils/PrintUtils.h"

namespace murphi {
std::string Decls::getAsString() {
  std::vector<std::string> text;
  for (IDecl* dec : decls) {
    if (auto* cd = dynamic_cast<murphi::ConstDecl*>(dec)) {
      text.push_back("const " + cd->getAsString() + ";");
    } else if (auto* cd = dynamic_cast<murphi::TypeDecl*>(dec)) {
      text.push_back("type " + cd->getAsString() + ";");
    } else if (auto* cd = dynamic_cast<murphi::VarDecl*>(dec)) {
      text.push_back("var " + cd->getAsString() + ";");
    }
  }
  return utils::interleave(text, " ");
}
bool Decls::isValidReference(std::string& id) {
  for (IDecl* d : decls) {
    if (d->getId() == id) {
      return true;
    }
  }
  return false;
}
}  // namespace murphi
