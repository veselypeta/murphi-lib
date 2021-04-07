#include "models/TypeDecl.h"
#include <string>

namespace murphi
{
    std::string TypeDecl::getAsString(){
        return id + " : " + expr->getAsString();
    }
} // namespace murphi
