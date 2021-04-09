#pragma once
#include "interfaces/Identifyable.h"
#include "interfaces/Printable.h"
#include "models/Decl.h"
#include "models/TypeExpr.h"
#include "models/Formal.h"
#include <string>
#include <vector>

namespace murphi {
namespace proc {

/*	<procdecl> ::=	<procedure>
                     | 	<function>
               */
class ProcDecl : public Printable<ProcDecl>, public Identifyable<ProcDecl> {
public:
  ProcDecl() {}
  virtual ~ProcDecl() {}
  virtual std::string getAsString() = 0;
  virtual std::string getId() = 0;
};

/*
        <function> ::=	function <ID> \( [ <formal> { ; <formal> } ] \)
                        : <typeExpr>;
                        [ { <decl> } begin ] [ <stmts> ] end;
*/
class Function : public ProcDecl {
public:
  Function() {}
  ~Function() { delete rv; }
  virtual std::string getAsString();
  virtual std::string getId();
  void addFormalParameter(Formal pram);

private:
  std::string id;
  TypeExpr *rv;
  std::vector<Formal> params;
  Decl forwardDecls;
  // stmts
};

/*
        <procedure> ::=	procedure <ID> \( [ <formal> { ; <formal> } ] \) ;
                        [ { <decl> } begin ] [ <stmts> ] end;
*/
class Procedure : public ProcDecl {
public:
  virtual std::string getAsString();
  virtual std::string getId();
  void addFormalParameter(Formal pram);

private:
  std::string id;
  std::vector<Formal> params;
  Decl forwardDecls;
  // stmts
};

} // namespace proc
} // namespace murphi
