#include "models/Expr.h"
#include <string>
#include "models/TypeExpr.h"

namespace murphi {

std::string IntExpr::getAsString() {
  return std::to_string(exprVal);
}

std::string AddExpr::getAsString() {
  return lhs->getAsString() + " + " + rhs->getAsString();
}

std::string SubExpr::getAsString() {
  return lhs->getAsString() + " - " + rhs->getAsString();
}

std::string MultExpr::getAsString() {
  return lhs->getAsString() + " * " + rhs->getAsString();
}
std::string DivExpr::getAsString() {
  return lhs->getAsString() + " / " + rhs->getAsString();
}
std::string RemExpr::getAsString() {
  return lhs->getAsString() + " % " + rhs->getAsString();
}

std::string LogNegExpr::getAsString() {
  return "!" + expr->getAsString();
}

std::string LogDisjExpr::getAsString() {
  return lhs->getAsString() + " | " + rhs->getAsString();
}

std::string LogConjExpr::getAsString() {
  return lhs->getAsString() + " & " + rhs->getAsString();
}

std::string LogImplExpr::getAsString() {
  return lhs->getAsString() + " -> " + rhs->getAsString();
}

std::string LTExpr::getAsString() {
  return lhs->getAsString() + " < " + rhs->getAsString();
}

std::string LTEQExpr::getAsString() {
  return lhs->getAsString() + " <= " + rhs->getAsString();
}

std::string GTExpr::getAsString() {
  return lhs->getAsString() + " < " + rhs->getAsString();
}

std::string GTEQExpr::getAsString() {
  return lhs->getAsString() + " <= " + rhs->getAsString();
}

std::string EQExpr::getAsString() {
  return lhs->getAsString() + " = " + rhs->getAsString();
}

std::string NEQExpr::getAsString() {
  return lhs->getAsString() + " != " + rhs->getAsString();
}

std::string CondExpr::getAsString() {
  return condExpr->getAsString() + " ? " + thenExpr->getAsString() + " : " +
         elseExpr->getAsString();
}

std::string ParenthExpr::getAsString() {
  return "(" + ex->getAsString() + ")";
}

// -- designator
std::string Designator::getAsString() {
  std::string s = id;
  for (Container idx : indexes) {
    s += idx.getAsString();
  }
  return s;
}

void Designator::addIndex(std::string fieldId) {
  indexes.push_back(Container(fieldId));
}

void Designator::addIndex(Expr* arrayIndx) {
  indexes.push_back(Container(arrayIndx));
}

// Undef
std::string IsUndefExpr::getAsString() {
  return "ISUNDEFINED( " + des->getAsString() + " )";
}

// is member

std::string IsMemberExpr::getAsString() {
  return "ISMEMBER( " + des->getAsString() + "," + tyexpr->getAsString() + " )";
}

IsMemberExpr::~IsMemberExpr() {
  delete des;
  delete tyexpr;
}

// multiset count
std::string MultiSetCountExpr::getAsString() {
  return "MultisetCount(" + var + " : " + expr->getAsString() + ", true)";
}

}  // namespace murphi
