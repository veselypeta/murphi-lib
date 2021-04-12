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
class Rule : public Printable<Rule> {
public:
  Rule() {}
  virtual ~Rule() {}
  virtual std::string getAsString() = 0;
};

/* <rules> ::= <rule> {; <rule> } [;] */
class Rules : Printable<Rules> {
public:
  Rules() {}
  ~Rules() { rules.clear(); }
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
class SimpleRule : public Rule {
public:
  SimpleRule(std::string ruleName, Expr *ruleExpr)
      : ruleName{ruleName}, ruleExpr{ruleExpr} {}
  ~SimpleRule() { delete ruleExpr; }
  virtual std::string getAsString();

  // These fields are public to allow the library user to do things such as .
  // obj.statements.addStatement(s);
  Decls declarations;
  Stmts statements;

private:
  std::string ruleName;
  Expr *ruleExpr;
};

/*
        <startstate> ::= startstate [ <string> ]
                           [ { <decl> } begin ]
                           [ <stmts> ]
                         end
*/
class StartState : public Rule {
public:
  StartState() {}
  StartState(std::string startStateName) : startStateName{startStateName} {}
  virtual std::string getAsString();

  Decls decls;
  Stmts statements;

private:
  std::string startStateName;
};

/*
  <invariant> ::= invariant [ <string> ] <expr>
*/
class Invariant : public Rule {
public:
  explicit Invariant(Expr *invExpr) : invExpr{invExpr} {}
  Invariant(std::string invName, Expr *invExpr)
      : invariantName{invName}, invExpr{invExpr} {}
  ~Invariant() { delete invExpr; }
  virtual std::string getAsString();

private:
  std::string invariantName;
  Expr *invExpr;
};

/*
        <ruleset> ::= ruleset <quantifier>
                      {; <quantifier> } do [<rules>] end
*/

class RuleSet : public Rule {
public:
  RuleSet(Quantifier *q) { quants.push_back(q); };
  void addRule(Rule *r) { rules.addRule(r); }
  virtual std::string getAsString();

private:
  Rules rules;
  std::vector<Quantifier *> quants;
};
} // namespace murphi
