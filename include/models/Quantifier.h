#pragma once
#include "models/TypeExpr.h"
#include "utils/PrintUtils.h"
#include <string>

namespace murphi {
/*
<quantifier> ::= <ID> : <typeExpr>
                   | <ID> := <expr> to <expr> [ by <expr> ]
*/

// TODO -- currently implementing the basic quantifier
class Quantifier : Printable<Quantifier> {
public:
  Quantifier(std::string id, TypeExpr *tyExpr) : id{id}, tyExpr{tyExpr} {}
  ~Quantifier() { delete tyExpr; }
  std::string getAsString() { return id + " : " + tyExpr->getAsString(); }

private:
  std::string id;
  TypeExpr *tyExpr;
};
} // namespace murphi