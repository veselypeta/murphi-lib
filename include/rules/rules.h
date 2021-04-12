#pragma once
#include "interfaces/Printable.h"
#include "models/Decl.h"
#include "models/Expr.h"
#include "proc/Statements.h"
#include <string>
#include <vector>
namespace murphi {
/*
        <rule> ::= <simplerule>
                 | <startstate>
                 | <invariant>
                 | <ruleset>
                 | <aliasrule>
*/
class Rule : Printable<Rule> {
public:
  virtual std::string getAsString() = 0;
};

/* <rules> ::= <rule> {; <rule> } [;] */
class Rules : Printable<Rules> {
public:
  void addRule(Rule *r);
  std::string getAsString();

private:
  std::vector<Rule *> rules;
};

/*
        <simplerule> ::= rule [<string>]
                           [ <expr> ==> ]
                           [ { <decl> } begin ]
                           [ stmts ]
                         end
*/
class SimpleRule : Rule {
public:
  SimpleRule(std::string ruleName, Expr *ruleExpr)
      : ruleName{ruleName}, ruleExpr{ruleExpr} {}
  virtual std::string getAsString();

  // These fields are public to allow the library user to do things such as .
  // obj.statements.addStatement(s);
  Decls declarations;
  Stmts statements;

private:
  std::string ruleName;
  Expr *ruleExpr;
};

} // namespace murphi
