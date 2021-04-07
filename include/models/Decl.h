#pragma once
#include "interfaces/Printable.h"
#include "models/ConstDecl.h"
#include <string>
#include <vector>

namespace murphi {
class Decl : public Printable<Decl> {
public:
  Decl() {}
  ~Decl() { constDecls.clear(); }
  void addConstDecl(ConstDecl *cd) { constDecls.push_back(cd); }
  std::string getAsString();

private:
  std::vector<ConstDecl *> constDecls;
};

} // namespace murphi
