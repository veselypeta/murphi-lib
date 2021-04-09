#include "proc/Statements.h"

namespace murphi {

std::string Stmts::getAsString() {
  std::string s;
  for (auto *stmt : stmts) {
    s += stmt->getAsString() + ";";
  }
  return s;
}

void Stmts::addStatement(Stmt *s) { return stmts.push_back(s); }

bool Stmts::isEmpty() { return stmts.size() == 0; }

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
  if (!elseStmts.isEmpty()){
    s += " else ";
    s += elseStmts.getAsString();
  }
  s += " endif";
  return s;
}

void IfStmt::addElseStatement(Stmt *s){
  return elseStmts.addStatement(s);
}

void IfStmt::addThenStatement(Stmt *s){
  return thenStmts.addStatement(s);
}

} // namespace murphi
