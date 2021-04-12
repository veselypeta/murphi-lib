#pragma once
#include "interfaces/Identifyable.h"
#include "interfaces/Printable.h"
#include <string>
#include <vector>

namespace murphi {

/*
        <decl> ::=	const { <constdecl> ; }
                 |	type { <typedecl> ; }
                 |	var { <vardecl> ; }

*/
class IDecl : public Printable<IDecl>, Identifyable<IDecl> {
public:
  IDecl(){}
  virtual ~IDecl(){}
  virtual std::string getAsString() = 0;
  virtual std::string getId() = 0;
};

class Decls : Printable<Decls> {
public:
  std::string getAsString();
  void addDecl(IDecl *decl) { decls.push_back(decl); };
  bool isValidReference(std::string id);

private:
  std::vector<IDecl *> decls;
};

} // namespace murphi
