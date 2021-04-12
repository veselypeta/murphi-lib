#include "rules/rules.h"

namespace murphi {
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
} // namespace murphi
