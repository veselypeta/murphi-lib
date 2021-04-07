#include "models/ConstDecl.h"

std::string murphi::ConstDecl::getAsString(){
    return id + " : " + expression->getAsString();
}
