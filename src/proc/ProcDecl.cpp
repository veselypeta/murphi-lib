#include "proc/ProcDecl.h"

namespace murphi {
namespace proc {

std::string Function::getId() {
  return id;
}

std::string Function::getAsString() {
  return "function " + getId() + "(" /* parameters*/ +
         ") : " + rv->getAsString() + ";" + forwardDecls.getAsString() +
         "begin" /*smts*/ + "end;";
}

std::string Procedure::getId() {
  return id;
}

std::string Procedure::getAsString() {
  return "procedure " + getId() + "(" /*parameters*/ + ");" +
         forwardDecls.getAsString() + "begin" /*stmts*/ + "end;";
}

}  // namespace proc
}  // namespace murphi
