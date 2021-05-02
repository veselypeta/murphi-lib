#pragma once
#include <string>
#include <vector>
#include "interfaces/Printable.h"
#include "models/Expr.h"
#include "models/Quantifier.h"

namespace murphi {
/*
  <stmt> ::= <assignment>         -- assignment --
    | <ifstmt>         -- if statement --
    | <switchstmt> -- switch statement --
    | <forstmt>    -- for statement --
    | <whilestmt>  -- while statement --
    | <aliasstmt>  -- alias statement --
    | <proccall>   -- procedure call --
    | <clearstmt>  -- clear statement --
    | <errorstmt>  -- error assertion --
    | <assertstmt> -- assertion --
    | <putstmt>    -- output statement --
    | <returnstmt> -- function return --
              */
class Stmt : public Printable<Stmt> {
 public:
  std::string getAsString() override = 0;
  virtual ~Stmt() = default;
};

// <stmts> ::= <stmt> {; [<stmt>] }
class Stmts : public Printable<Stmts> {
 public:
  std::string getAsString() override;
  void addStatement(Stmt* s);
  bool isEmpty();

 private:
  std::vector<Stmt*> stmts;
};

// <assignment> ::= <designator> := <expression>
class Assignment : public Stmt {
 public:
  Assignment(Designator* des, Expr* expr) : des{des}, expr{expr} {}
  ~Assignment() override {
    delete des;
    delete expr;
  }
  std::string getAsString() override;

 private:
  Designator* des;
  Expr* expr;
};

/*
        <ifstmt> ::= if <expr> then [ <stmts> ]
                        { elsif <expr> then [ <stmts> ] }
                        [ else [ <stmts> ] ]
                     endif
*/
class IfStmt : public Stmt {
 public:
  explicit IfStmt(Expr* ifExpr) : ifExpr{ifExpr} {}
  ~IfStmt() override { delete ifExpr; }
  std::string getAsString() override;
  void addThenStatement(Stmt* s);
  void addElseStatement(Stmt* s);

 private:
  Expr* ifExpr;
  Stmts thenStmts;
  Stmts elseStmts;
};

/*
        <switchstmt> ::= switch <expr>
                           { case <expr> {, expr} : [ <stmts> ] }
                           [ else [ <stmts> ] ]
                         endswitch

*/

class CaseStmt : public Printable<CaseStmt> {
 public:
  explicit  CaseStmt(Expr* ce) { caseExprs.push_back(ce); }
  ~CaseStmt() { caseExprs.clear(); }
  std::string getAsString() override;
  void addCaseExpr(Expr* e);
  void addCaseStatement(Stmt* s);

 private:
  std::vector<Expr*> caseExprs;
  Stmts caseStmts;
};

class SwitchStmt : public Stmt {
 public:
  explicit SwitchStmt(Expr* switchExpr) : swExpr{switchExpr} {}
  ~SwitchStmt() override { delete swExpr; }
  std::string getAsString() override;
  void addCaseStmt(CaseStmt c) { caseStmts.push_back(std::move(c)); };
  void addElseStmt(Stmt* s) { elseStmts.addStatement(s); };

 private:
  Expr* swExpr;
  std::vector<CaseStmt> caseStmts;
  Stmts elseStmts;
};

/* <forstmt> ::= for <quantifier> do [stmts] endfor*/
class ForStmt : public Stmt {
 public:
  explicit ForStmt(Quantifier* q) : quant{q} {}
  std::string getAsString() override;
  void addStatement(Stmt* s) { stmts.addStatement(s); }

 private:
  Quantifier* quant;
  Stmts stmts;
};

// <whilestmt> ::= while <expr> do [stmts] end //
class WhileStmt : public Stmt {
 public:
  explicit WhileStmt(Expr* expr) : expr{expr} {}
  ~WhileStmt() override { delete expr; }
  std::string getAsString() override;
  void addStatement(Stmt* s) { stmts.addStatement(s); }

 private:
  Expr* expr;
  Stmts stmts;
};

/*
        <aliasstmt> ::= alias <alias> { ; <alias> } do [ <stmts> ] end

        <alias> ::= <ID> : <expr>
*/
class Alias : public Printable<Alias> {
 public:
  Alias(std::string id, Expr* expr) : id{std::move(id)}, expr{expr} {}
  ~Alias() { delete expr; }
  std::string getAsString() override { return id + " : " + expr->getAsString(); }

 private:
  std::string id;
  Expr* expr;
};

class AliasStmt : public Stmt {
 public:
  explicit AliasStmt(Alias* a) { aliasses.push_back(a); }
  ~AliasStmt() override { aliasses.clear(); }
  std::string getAsString() override;
  void addStatement(Stmt* s) { stmts.addStatement(s); }

 private:
  std::vector<Alias*> aliasses;
  Stmts stmts;
};

/*<proccall> ::= <ID> \( <expr> {, <expr> } \)*/
class ProcCall : public Stmt {
 public:
  explicit ProcCall(std::string procId, Expr* e) : id{std::move(procId)} {
    exprs.push_back(e);
  }
  ~ProcCall() override { exprs.clear(); }
  std::string getAsString() override;
  void addArgument(Expr* x) { exprs.push_back(x); }

 private:
  std::string id;
  std::vector<Expr*> exprs;
};

/* <clearstmt> ::= clear <designator> */
class ClearStmt : public Stmt {
 public:
  explicit ClearStmt(Designator* des) : des{des} {}
  ~ClearStmt() override { delete des; }
  std::string getAsString() override { return "clear " + des->getAsString(); }

 private:
  Designator* des;
};

/* <errorstmt> ::= error <string> */
class ErrorStmt : public Stmt {
 public:
  explicit ErrorStmt(std::string msg) : msg{std::move(msg)} {};
  std::string getAsString() override { return "error \"" + msg + "\""; }

 private:
  std::string msg;
};

/* <assertstmt> ::= assert <expr> [ <string> ] */
class AssertStmt : public Stmt {
 public:
  explicit AssertStmt(Expr* expr) : expr{expr} {}
  explicit AssertStmt(Expr* expr, std::string msg) : expr{expr}, msg{std::move(msg)} {}
  ~AssertStmt() override { delete expr; }
  std::string getAsString() override;

 private:
  Expr* expr;
  std::string msg;
};

/* <putstmt> ::= put ( <expr> | <string> ) */
class PutStmt : public Stmt {
 public:
  explicit PutStmt(std::string val) : val{std::move(val)}, type{STRING} {}
  explicit PutStmt(Expr* expr) : expr{expr}, type{EXPR} {}
  ~PutStmt() override {
    if (this->type == EXPR) {
      delete expr;
    }
  }
  std::string getAsString() override;

 private:
  typedef enum { STRING, EXPR } putType;
  putType type;
  Expr* expr;
  std::string val;
};

/* <returnstmt> ::= return [ <expr> ] */
class ReturnStmt : public Stmt {
 public:
  ReturnStmt() : expr{nullptr} {}
  explicit ReturnStmt(Expr* expr) : expr{expr} {}
  ~ReturnStmt() override { delete expr; }
  std::string getAsString() override;

 private:
  Expr* expr;
};

/* undefinestmt	: UNDEFINE designator; */
class UndefineStmt : public Stmt {
 public:
  explicit UndefineStmt(Designator* des) : des{des} {}
  ~UndefineStmt() override { delete des; }

  std::string getAsString() override;

 private:
  Designator* des;
};

class MultiSetAddStmt : public Stmt {
 public:
  MultiSetAddStmt(murphi::Designator* msg, murphi::Designator* net)
      : msg{msg}, net{net} {}
  ~MultiSetAddStmt() override {
    delete msg;
    delete net;
  }

  std::string getAsString() override;

 private:
  Designator* msg;
  Designator* net;
};

class MultiSetRemoveStmt : public Stmt {
 public:
  MultiSetRemoveStmt(murphi::Designator* msg, murphi::Designator* net)
      : msg{msg}, net{net} {}
  ~MultiSetRemoveStmt() override {
    delete msg;
    delete net;
  }

  std::string getAsString() override;

 private:
  Designator* msg;
  Designator* net;
};

}  // namespace murphi