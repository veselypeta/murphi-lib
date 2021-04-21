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
  virtual std::string getAsString() = 0;
  virtual ~Stmt() {}
};

// <stmts> ::= <stmt> {; [<stmt>] }
class Stmts : public Printable<Stmts> {
 public:
  std::string getAsString();
  void addStatement(Stmt* s);
  bool isEmpty();

 private:
  std::vector<Stmt*> stmts;
};

// <assignment> ::= <designator> := <expression>
class Assignment : public Stmt {
 public:
  Assignment(Designator* des, Expr* expr) : des{des}, expr{expr} {}
  ~Assignment() {
    delete des;
    delete expr;
  }
  virtual std::string getAsString();

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
  IfStmt(Expr* ifExpr) : ifExpr{ifExpr} {}
  ~IfStmt() { delete ifExpr; }
  virtual std::string getAsString();
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
  CaseStmt(Expr* ce) { caseExprs.push_back(ce); }
  ~CaseStmt() { caseExprs.clear(); }
  std::string getAsString();
  void addCaseExpr(Expr* e);
  void addCaseStatement(Stmt* s);

 private:
  std::vector<Expr*> caseExprs;
  Stmts caseStmts;
};

class SwitchStmt : public Stmt {
 public:
  SwitchStmt(Expr* switchExpr) : swExpr{switchExpr} {}
  ~SwitchStmt() { delete swExpr; }
  virtual std::string getAsString();
  void addCaseStmt(CaseStmt c) { caseStmts.push_back(c); };
  void addElseStmt(Stmt* s) { elseStmts.addStatement(s); };

 private:
  Expr* swExpr;
  std::vector<CaseStmt> caseStmts;
  Stmts elseStmts;
};

/* <forstmt> ::= for <quantifier> do [stmts] endfor*/
class ForStmt : public Stmt {
 public:
  ForStmt(Quantifier* q) : quant{q} {}
  virtual std::string getAsString();
  void addStatement(Stmt* s) { stmts.addStatement(s); }

 private:
  Quantifier* quant;
  Stmts stmts;
};

// <whilestmt> ::= while <expr> do [stmts] end //
class WhileStmt : public Stmts {
 public:
  WhileStmt(Expr* expr) : expr{expr} {}
  ~WhileStmt() { delete expr; }
  virtual std::string getAsString();
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
  Alias(std::string id, Expr* expr) : id{id}, expr{expr} {}
  ~Alias() { delete expr; }
  std::string getAsString() { return id + " : " + expr->getAsString(); }

 private:
  std::string id;
  Expr* expr;
};

class AliasStmt : public Stmt {
 public:
  explicit AliasStmt(Alias* a) { aliasses.push_back(a); }
  ~AliasStmt() { aliasses.clear(); }
  virtual std::string getAsString();
  void addStatement(Stmt* s) { stmts.addStatement(s); }

 private:
  std::vector<Alias*> aliasses;
  Stmts stmts;
};

/*<proccall> ::= <ID> \( <expr> {, <expr> } \)*/
class ProcCall : public Stmt {
 public:
  explicit ProcCall(std::string procId, Expr* e) : id{procId} {
    exprs.push_back(e);
  }
  ~ProcCall() { exprs.clear(); }
  virtual std::string getAsString();
  void addArgument(Expr* x) { exprs.push_back(x); }

 private:
  std::string id;
  std::vector<Expr*> exprs;
};

/* <clearstmt> ::= clear <designator> */
class ClearStmt : public Stmt {
 public:
  explicit ClearStmt(Designator* des) : des{des} {}
  ~ClearStmt() { delete des; }
  virtual std::string getAsString() { return "clear " + des->getAsString(); }

 private:
  Designator* des;
};

/* <errorstmt> ::= error <string> */
class ErrorStmt : public Stmt {
 public:
  explicit ErrorStmt(std::string msg) : msg{msg} {};
  virtual std::string getAsString() { return "error \"" + msg + "\""; }

 private:
  std::string msg;
};

/* <assertstmt> ::= assert <expr> [ <string> ] */
class AssertStmt : public Stmt {
 public:
  explicit AssertStmt(Expr* expr) : expr{expr} {}
  explicit AssertStmt(Expr* expr, std::string msg) : expr{expr}, msg{msg} {}
  ~AssertStmt() { delete expr; }
  virtual std::string getAsString();

 private:
  Expr* expr;
  std::string msg;
};

/* <putstmt> ::= put ( <expr> | <string> ) */
class PutStmt : public Stmt {
 public:
  PutStmt(std::string val) : val{val}, type{STRING} {}
  PutStmt(Expr* expr) : expr{expr}, type{EXPR} {}
  ~PutStmt() {
    if (this->type == EXPR) {
      delete expr;
    }
  }
  virtual std::string getAsString();

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
  ReturnStmt(Expr* expr) : expr{expr} {}
  ~ReturnStmt() { delete expr; }
  virtual std::string getAsString();

 private:
  Expr* expr;
};

/* undefinestmt	: UNDEFINE designator; */
class UndefineStmt : public Stmt {
 public:
  UndefineStmt(Designator* des) : des{des} {}
  ~UndefineStmt() { delete des; }

  virtual std::string getAsString();

 private:
  Designator* des;
};

}  // namespace murphi