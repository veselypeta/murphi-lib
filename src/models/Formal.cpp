#include "models/Formal.h"
#include "utils/PrintUtils.h"
#include <string>

namespace murphi {
// ----- FORMAL ----- //
/*
<formal> ::=	[var] <ID> { , <ID> } : <typeExpr>
*/
std::string Formal::getAsString() {
  return "var " + ::murphi::utils::interleaveComma(ids) + " : " +
         expr->getAsString();
}

void Formal::addFormalIdent(std::string id) { return ids.push_back(id); }
} // namespace murphi
