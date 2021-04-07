#include "models/TypeDecl.h"
#include <string>

namespace murphi
{
    std::string TypeDecl::getAsString(){
        assert(expr->getAsString() != "" && "somehow got empty string!");
        return id + " : " + expr->getAsString() + ";";
    }
} // namespace murphi
