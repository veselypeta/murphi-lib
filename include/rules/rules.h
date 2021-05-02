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
  Rule() = default;
  virtual ~Rule() = default;
  std::string getAsString() override = 0;
};

/* <rules> ::= <rule> {; <rule> } [;] */
class Rules : Printable<Rules> {
public:
  Rules() = default;
  ~Rules() { rules.clear(); }
  void addRule(Rule *r);
  std::string getAsString() override;

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
      : ruleName{std::move(ruleName)}, ruleExpr{ruleExpr} {}
  ~SimpleRule() override { delete ruleExpr; }
  std::string getAsString() override;

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
  StartState() = default;
  explicit StartState(std::string startStateName)
      : startStateName{std::move(startStateName)} {}
  std::string getAsString() override;

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
      : invariantName{std::move(invName)}, invExpr{invExpr} {}
  ~Invariant() override { delete invExpr; }
  std::string getAsString() override;

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
  explicit RuleSet(Quantifier *q) { quants.push_back(q); };
  void addRule(Rule *r) { rules.addRule(r); }
  std::string getAsString() override;

private:
  Rules rules;
  std::vector<Quantifier *> quants;
};

/*
        <aliasrule> ::= alias <alias> {; <alias> } do [<rules>] end
*/

class AliasRule : public Rule {
public:
  explicit AliasRule(Alias *a) { aliasses.push_back(a); }
  ~AliasRule() override { aliasses.clear(); }
  std::string getAsString() override;
  void addRule(Rule *r) { rules.addRule(r); }

private:
  std::vector<Alias *> aliasses;
  Rules rules;
};

class ChooseRule : public Rule {
public:
  explicit ChooseRule(Quantifier *qf) : qf{qf} {}
  ~ChooseRule() override { delete qf; }
  void addRule(Rule *rule) { rules.addRule(rule); }
  std::string getAsString() override;

private:
  Quantifier *qf;
  Rules rules;
};

} // namespace murphi
