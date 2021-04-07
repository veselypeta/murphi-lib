#pragma once
#include "interfaces/Printable.h"
#include "models/ConstDecl.h"
#include "models/TypeDecl.h"
#include <string>
#include <vector>

namespace murphi {
class Decl : public Printable<Decl> {
public:
  Decl() {}
  ~Decl() { constDecls.clear(); }
  void addConstDecl(ConstDecl *cd) { constDecls.push_back(cd); }
  void addTypeDecl(TypeDecl *td) { typeDecls.push_back(td); }
  std::string getAsString();
  bool isValidReference(std::string id);

private:
  std::vector<ConstDecl *> constDecls;
  std::vector<TypeDecl *> typeDecls;
};

} // namespace murphi
