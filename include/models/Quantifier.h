#pragma once
#include <string>
#include "models/TypeExpr.h"
#include "utils/PrintUtils.h"

namespace murphi {
/*
<quantifier> ::= <ID> : <typeExpr>
                   | <ID> := <expr> to <expr> [ by <expr> ]
*/

// TODO -- currently implementing the basic quantifier
class Quantifier : Printable<Quantifier> {
 public:
  Quantifier(std::string id, TypeExpr* tyExpr) : id{std::move(id)}, tyExpr{tyExpr} {}
  ~Quantifier() { delete tyExpr; }
  std::string getAsString() override { return id + " : " + tyExpr->getAsString(); }

 private:
  std::string id;
  TypeExpr* tyExpr;
};
}  // namespace murphi
