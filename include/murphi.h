#pragma once
#include <string>
#include <vector>
#include "models/Decl.h"
#include "models/Expr.h"

namespace murphi {
class Module {
 public:
  /**
  Add a constant declaration to the Murphi Module (integer only)
*/
  void addConstDecl(std::string id, Expr* expr);

  /**
  Returns Murphi code as a formatted String
*/
  std::string getAsString();

  /**
 Dump the module to stdout
*/
  void dump();

 private:
  Decl decls;
};
}  // namespace murphi
