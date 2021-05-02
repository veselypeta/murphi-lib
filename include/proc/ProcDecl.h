#pragma once
#include <string>
#include <vector>
#include "interfaces/Identifyable.h"
#include "interfaces/Printable.h"
#include "models/Decl.h"
#include "models/Formal.h"
#include "models/TypeExpr.h"

namespace murphi::proc {

/*	<procdecl> ::=	<procedure>
                     | 	<function>
               */
class ProcDecl : public Printable<ProcDecl>, public Identifyable<ProcDecl> {
 public:
  ProcDecl() = default;
  virtual ~ProcDecl() = default;
  std::string getAsString() override = 0;
  virtual std::string getId() = 0;
};

/*
        <function> ::=	function <ID> \( [ <formal> { ; <formal> } ] \)
                        : <typeExpr>;
                        [ { <decl> } begin ] [ <stmts> ] end;
*/
class Function : public ProcDecl {
 public:
  Function() = default;
  ~Function() override { delete rv; }
  std::string getAsString() override;
  std::string getId() override;
  void addFormalParameter(Formal pram);

 private:
  std::string id;
  TypeExpr* rv{};
  std::vector<Formal> params;
  Decls forwardDecls;
  // stmts
};

/*
        <procedure> ::=	procedure <ID> \( [ <formal> { ; <formal> } ] \) ;
                        [ { <decl> } begin ] [ <stmts> ] end;
*/
// TODO -- needs to be tested!!
class Procedure : public ProcDecl {
 public:
  std::string getAsString() override;
  std::string getId() override;
  void addFormalParameter(Formal pram);

 private:
  std::string id;
  std::vector<Formal> params;
  Decls forwardDecls;
  // stmts
};

}  // namespace murphi
