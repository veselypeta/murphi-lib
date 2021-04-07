#pragma once
#include <string>
#include <vector>
#include "interfaces/Printable.h"
#include "models/ConstDecl.h"
#include "models/TypeDecl.h"
#include "models/VarDecl.h"

namespace murphi {
class Decl : public Printable<Decl> {
 public:
  Decl() {}
  ~Decl() {
    constDecls.clear();
    typeDecls.clear();
    varDecls.clear();
  }
  void addConstDecl(ConstDecl* cd) { constDecls.push_back(cd); }
  void addTypeDecl(TypeDecl* td) { typeDecls.push_back(td); }
  void addVarDecl(VarDecl* vd) { varDecls.push_back(vd); }
  std::string getAsString();
  bool isValidReference(std::string id);

 private:
  std::vector<ConstDecl*> constDecls;
  std::vector<TypeDecl*> typeDecls;
  std::vector<VarDecl*> varDecls;
};

}  // namespace murphi
