#pragma once
#include <string>
#include <vector>
#include "models/Decl.h"
#include "models/Expr.h"
#include "models/TypeExpr.h"

namespace murphi {
class Module {
 public:
  /**
  Add a constant declaration to the Murphi Module
*/
  void addConstDecl(std::string id, Expr* expr);

  /**
Add a Type declaration to the Murphi Module
*/
  void addTypeDecl(std::string id, TypeExpr* expr);

  /**
Returns true if a reference is valid (i.e. references a type/variable/function
etc.)
*/
  bool isVaidReference(std::string id);

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
