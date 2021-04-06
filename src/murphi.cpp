#include "murphi.h"
#include <iostream>
#include <string>

// <constdecl> ::=	<ID> : <expr>
void murphi::Module::addConstDecl(std::string id, murphi::Expr *expr) {
  // TODO -- add a constant to the module
}

std::string murphi::Module::getAsString() { return ""; }

void murphi::Module::dump() { std::cout << getAsString() << std::endl; }