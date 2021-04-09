#pragma once
#include "interfaces/Printable.h"
#include "models/Expr.h"
#include <string>
#include <vector>

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
  void addStatement(Stmt *s);
  bool isEmpty();

private:
  std::vector<Stmt *> stmts;
};

// <assignment> ::= <designator> := <expression>
class Assignment : public Stmt {
public:
  Assignment(Designator *des, Expr *expr) : des{des}, expr{expr} {}
  ~Assignment() {
    delete des;
    delete expr;
  }
  virtual std::string getAsString();

private:
  Designator *des;
  Expr *expr;
};

/*
        <ifstmt> ::= if <expr> then [ <stmts> ]
                        { elsif <expr> then [ <stmts> ] }
                        [ else [ <stmts> ] ]
                     endif
*/
class IfStmt : public Stmt {
public:
  IfStmt(Expr *ifExpr) : ifExpr{ifExpr} {}
  ~IfStmt(){
    delete ifExpr;
  }
  virtual std::string getAsString();
  void addThenStatement(Stmt *s);
  void addElseStatement(Stmt *s);

private:
  Expr *ifExpr;
  Stmts thenStmts;
  Stmts elseStmts;
};


} // namespace murphi
