#include "models/TypeDecl.h"
#include <string>

namespace murphi {
// <typedecl> ::=	<ID> : <typeExpr>
std::string TypeDecl::getAsString() { return id + " : " + expr->getAsString(); }
} // namespace murphi
