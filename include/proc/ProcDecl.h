#pragma once
#include <string>
#include "interfaces/Identifyable.h"
#include "interfaces/Printable.h"
#include "models/Decl.h"
#include "models/TypeExpr.h"

namespace murphi {
namespace proc {

class ProcDecl : public Printable<ProcDecl>, public Identifyable<ProcDecl> {
 public:
  ProcDecl() {}
  virtual ~ProcDecl() {}
  virtual std::string getAsString() = 0;
  virtual std::string getId() = 0;
};

class Function : public ProcDecl {
 public:
  Function() {}
  ~Function() { delete rv; }
  virtual std::string getAsString();
  virtual std::string getId();

 private:
  std::string id;
  TypeExpr* rv;
  Decl forwardDecls;
  // stmts
};

class Procedure : public ProcDecl {
 public:
  virtual std::string getAsString();
  virtual std::string getId();

 private:
  std::string id;
  Decl forwardDecls;
  // stmts
};

}  // namespace proc
}  // namespace murphi
