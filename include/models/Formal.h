#pragma once
#include <string>
#include <vector>
#include "interfaces/Printable.h"
#include "models/TypeExpr.h"

namespace murphi {
/*
<formal> ::=	[var] <ID> { , <ID> } : <typeExpr>
*/
class Formal : public Printable<Formal> {
 public:
  Formal(std::string id, TypeExpr* expr) : expr{expr} { ids.push_back(id); }
  ~Formal() { delete expr; }
  void addFormalIdent(std::string id);
  std::string getAsString();

 private:
  std::vector<std::string> ids;
  TypeExpr* expr;
};

}  // namespace murphi
