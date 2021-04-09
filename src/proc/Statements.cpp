#include "proc/Statements.h"
#include "utils/PrintUtils.h"

namespace murphi {

std::string Stmts::getAsString() {
  std::string s;
  for (auto* stmt : stmts) {
    s += stmt->getAsString() + ";";
  }
  return s;
}

void Stmts::addStatement(Stmt* s) {
  return stmts.push_back(s);
}

bool Stmts::isEmpty() {
  return stmts.size() == 0;
}

// --- Assignment -- //
std::string Assignment::getAsString() {
  return des->getAsString() + " := " + expr->getAsString();
}

// --- If-Statement -- //

std::string IfStmt::getAsString() {
  std::string s = "if ";
  s += ifExpr->getAsString();
  s += " then ";
  s += thenStmts.getAsString();
  if (!elseStmts.isEmpty()) {
    s += " else ";
    s += elseStmts.getAsString();
  }
  s += " endif";
  return s;
}

void IfStmt::addElseStatement(Stmt* s) {
  return elseStmts.addStatement(s);
}

void IfStmt::addThenStatement(Stmt* s) {
  return thenStmts.addStatement(s);
}

// --- Case-Statement -- //

std::string CaseStmt::getAsString() {
  std::string s = "case ";
  s += utils::interleaveComma(caseExprs);
  s += ": ";
  s += caseStmts.getAsString();
  return s;
}

void CaseStmt::addCaseStatement(Stmt* s) {
  caseStmts.addStatement(s);
}

void CaseStmt::addCaseExpr(Expr* e) {
  caseExprs.push_back(e);
}

// --- Switch-Statement -- //
std::string SwitchStmt::getAsString() {
  std::string s = "switch ";
  s += swExpr->getAsString();
  for (auto cs : caseStmts) {
    s += " ";
    s += cs.getAsString();
  }
  if (!elseStmts.isEmpty()) {
    s += " else ";
    s += elseStmts.getAsString();
  }
  s += " endswitch";
  return s;
}

}  // namespace murphi
