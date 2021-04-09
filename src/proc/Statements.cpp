#include "proc/Statements.h"
#include "utils/PrintUtils.h"

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
  if (!elseStmts.isEmpty()) {
    s += " else ";
    s += elseStmts.getAsString();
  }
  s += " endif";
  return s;
}

void IfStmt::addElseStatement(Stmt *s) { return elseStmts.addStatement(s); }

void IfStmt::addThenStatement(Stmt *s) { return thenStmts.addStatement(s); }

// --- Case-Statement -- //

std::string CaseStmt::getAsString() {
  std::string s = "case ";
  s += utils::interleaveComma(caseExprs);
  s += ": ";
  s += caseStmts.getAsString();
  return s;
}

void CaseStmt::addCaseStatement(Stmt *s) { caseStmts.addStatement(s); }

void CaseStmt::addCaseExpr(Expr *e) { caseExprs.push_back(e); }

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

// --- For-Statement -- //
std::string ForStmt::getAsString() {
  return "for " + quant->getAsString() + " do " + stmts.getAsString() +
         " endfor";
}

// --- While-Statement -- //
std::string WhileStmt::getAsString() {
  return "while " + expr->getAsString() + " do " + stmts.getAsString() + " end";
}

// --- Alias-Statement -- //
std::string AliasStmt::getAsString() {
  std::string s = "alias ";

  // get aliases as vector of strings
  std::vector<std::string> alnames;
  for (auto al : aliasses) {
    alnames.push_back(al->getAsString());
  }

  s += utils::interleave(alnames, ";");

  s += " do ";
  s += stmts.getAsString();
  s += " end";
  return s;
}

// --- ProcCall-Statement -- //
std::string ProcCall::getAsString() {
  return id + "(" + utils::interleaveComma(exprs) + ")";
}

// --- Assert-Statement -- //
std::string AssertStmt::getAsString() {
  std::string s = "assert ";
  s += expr->getAsString();
  if (msg != "") {
    s += " \"";
    s += msg;
    s += "\"";
  }
  return s;
}

// --- Put-Statement -- //
std::string PutStmt::getAsString() {
  if (type == EXPR) {
    return "put " + expr->getAsString();
  }
  return "put \"" + val + "\"";
}

std::string ReturnStmt::getAsString() {
  std::string s = "return";
  if (expr != nullptr) {
    s += " ";
    s += expr->getAsString();
  }
  return s;
}

} // namespace murphi
