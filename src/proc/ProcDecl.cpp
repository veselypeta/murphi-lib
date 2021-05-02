#include "proc/ProcDecl.h"
#include "utils/PrintUtils.h"

namespace murphi::proc {

// ----- FUNCTION ----- //

std::string Function::getId() {
  return id;
}

std::string Function::getAsString() {
  return "function " + getId() + "(" /* parameters*/ +
         ") : " + rv->getAsString() + ";" + forwardDecls.getAsString() +
         "begin" /*smts*/ + "end;";
}

void Function::addFormalParameter(Formal param) {
  return params.push_back(param);
}

// ----- PROCEDURE ----- //

std::string Procedure::getId() {
  return id;
}

std::string Procedure::getAsString() {
  return "procedure " + getId() + "(" /*parameters*/ + ");" +
         forwardDecls.getAsString() + "begin" /*stmts*/ + "end;";
}

void Procedure::addFormalParameter(Formal param) {
  return params.push_back(param);
}

}  // namespace murphi
