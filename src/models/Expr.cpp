#include "models/Expr.h"
#include <memory>

std::string murphi::IntExpr::getAsString(){
    return std::to_string(exprVal);
}

std::string murphi::AddExpr::getAsString(){
    return lhs->getAsString() + " + " + rhs->getAsString();
}

std::string murphi::ParenthExpr::getAsString(){
    return "(" + ex->getAsString() + ")";
}
