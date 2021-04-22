#include "rules/rules.h"

namespace murphi {

std::string Rules::getAsString() {
  std::string s;
  for (auto rule : rules) {
    s += rule->getAsString() + ";";
  }
  return s;
}

void Rules::addRule(Rule* r) {
  rules.push_back(r);
}

/*
        <simplerule> ::= rule [<string>]
                           [ <expr> ==> ]
                           [ { <decl> } begin ]
                           [ stmts ]
                         end
*/
std::string SimpleRule::getAsString() {
  return "rule \"" + ruleName + "\" " + ruleExpr->getAsString() + " ==> " +
         declarations.getAsString() + " begin " + statements.getAsString() +
         " end";
}

std::string StartState::getAsString() {
  return "startstate \"" + startStateName + "\" " + decls.getAsString() +
         " begin " + statements.getAsString() + " end";
}

std::string Invariant::getAsString() {
  return "invariant \"" + invariantName + "\" " + invExpr->getAsString();
};

std::string RuleSet::getAsString() {
  std::vector<std::string> qs;
  for (auto* q : quants) {
    qs.push_back(q->getAsString());
  }

  return "ruleset " + utils::interleave(qs, "; ") + " do " +
         rules.getAsString() + " end";
}

std::string AliasRule::getAsString() {
  std::vector<std::string> al;
  for (auto a : aliasses) {
    al.push_back(a->getAsString());
  }
  return "alias " + utils::interleave(al, "; ") + " do " + rules.getAsString() +
         " end";
}

std::string ChooseRule::getAsString() {
  return "Choose " + qf->getAsString() + " Do " + rules.getAsString() +
         " EndChoose";
}

}  // namespace murphi
