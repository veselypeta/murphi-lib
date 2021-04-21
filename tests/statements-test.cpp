#include "proc/Statements.h"
#include <gtest/gtest.h>

// Statments
TEST(StmtSuite, AssignmentPrint) {
  murphi::Designator* d = new murphi::Designator("dir");
  murphi::Expr* i = new murphi::IntExpr(1);
  murphi::Stmt* s = new murphi::Assignment(d, i);

  EXPECT_STREQ(s->getAsString().c_str(), "dir := 1");

  delete s;
}

TEST(StmtSuite, IfStmtThenOnlyPrint) {
  murphi::Expr* a = new murphi::IntExpr(1);
  murphi::Expr* b = new murphi::IntExpr(5);
  murphi::Expr* c = new murphi::EQExpr(a, b);

  murphi::IfStmt* f = new murphi::IfStmt(c);

  murphi::Designator* d = new murphi::Designator("dir");
  murphi::Expr* i = new murphi::IntExpr(1);
  murphi::Stmt* s = new murphi::Assignment(d, i);

  f->addThenStatement(s);

  EXPECT_STREQ(f->getAsString().c_str(), "if 1 = 5 then dir := 1; endif");

  delete f;
}

TEST(StmtSuite, IfStmtThenElsePrint) {
  murphi::Expr* a = new murphi::IntExpr(1);
  murphi::Expr* b = new murphi::IntExpr(5);
  murphi::Expr* c = new murphi::EQExpr(a, b);

  murphi::IfStmt* f = new murphi::IfStmt(c);

  murphi::Designator* d = new murphi::Designator("dir");
  murphi::Expr* i = new murphi::IntExpr(1);
  murphi::Stmt* s = new murphi::Assignment(d, i);

  murphi::Designator* d2 = new murphi::Designator("cache");
  murphi::Expr* i2 = new murphi::IntExpr(7);
  murphi::Stmt* s2 = new murphi::Assignment(d2, i2);

  f->addThenStatement(s);
  f->addElseStatement(s2);

  EXPECT_STREQ(f->getAsString().c_str(),
               "if 1 = 5 then dir := 1; else cache := 7; endif");

  delete f;
}

TEST(StmtSuite, CaseStatment) {
  // generate the guard
  murphi::Expr* caseExpr = new murphi::Designator("GetM_Ack_D");
  murphi::CaseStmt cstmt(caseExpr);
  // case expr
  murphi::Designator* des = new murphi::Designator("State");
  murphi::Designator* val = new murphi::Designator("I");
  murphi::Stmt* caseStmt = new murphi::Assignment(des, val);
  // add the stament to the case body
  cstmt.addCaseStatement(caseStmt);

  EXPECT_STREQ(cstmt.getAsString().c_str(), "case GetM_Ack_D: State := I;");
}

TEST(StmtSuite, SwitchStatment) {
  // generate the switch expression
  murphi::Designator* swExpr = new murphi::Designator("cache_entry");
  swExpr->addIndex("State");

  // generate the swithc stmt obj
  murphi::SwitchStmt switchStmt(swExpr);

  // add a case stmt to the switch
  murphi::Designator* caseExpr = new murphi::Designator("GetM_Ack_AD");
  murphi::CaseStmt caseStmt = murphi::CaseStmt(caseExpr);
  murphi::Designator* des = new murphi::Designator("cache_entry");
  des->addIndex("State");
  murphi::Designator* val = new murphi::Designator("M");
  murphi::Stmt* csStmt = new murphi::Assignment(des, val);
  caseStmt.addCaseStatement(csStmt);
  switchStmt.addCaseStmt(caseStmt);

  // add an else stmt
  murphi::Designator* elseDes = new murphi::Designator("cache_entry");
  elseDes->addIndex("State");
  murphi::Designator* elseVal = new murphi::Designator("M_evict");
  murphi::Assignment* elseStmt = new murphi::Assignment(elseDes, elseVal);
  switchStmt.addElseStmt(elseStmt);

  EXPECT_STREQ(switchStmt.getAsString().c_str(),
               "switch cache_entry.State case GetM_Ack_AD: cache_entry.State "
               ":= M; else cache_entry.State := M_evict; endswitch");
}

TEST(StmtSuite, ForStmt) {
  // generate the range to loop over
  murphi::IntExpr* start = new murphi::IntExpr(0);
  murphi::IntExpr* end = new murphi::IntExpr(10);
  murphi::IntegerSubRange* range = new murphi::IntegerSubRange(start, end);
  murphi::Quantifier* q = new murphi::Quantifier("i", range);

  murphi::ForStmt forStmt(q);

  // add some statements
  murphi::Designator* des = new murphi::Designator("cache_entry");
  des->addIndex("State");
  murphi::Designator* rhs = new murphi::Designator("I_load");
  murphi::Assignment* as = new murphi::Assignment(des, rhs);

  forStmt.addStatement(as);

  EXPECT_STREQ(forStmt.getAsString().c_str(),
               "for i : 0 .. 10 do cache_entry.State := I_load; endfor");
}

TEST(StmtSuite, WhileStmt) {
  // generate a condition
  murphi::IntExpr* lhs = new murphi::IntExpr(0);
  murphi::Designator* rhs = new murphi::Designator("val");
  murphi::LTExpr* lte = new murphi::LTExpr(lhs, rhs);

  // while statement
  murphi::WhileStmt ws(lte);

  // add a stmt
  murphi::Designator* des = new murphi::Designator("cache_entry");
  des->addIndex("State");
  murphi::Designator* a = new murphi::Designator("I_load");
  murphi::Assignment* b = new murphi::Assignment(des, a);
  ws.addStatement(b);

  EXPECT_STREQ(ws.getAsString().c_str(),
               "while 0 < val do cache_entry.State := I_load; end");
}

TEST(StmtSuite, AliasStmt) {
  std::string expectedText = "alias msg : cache_entry.msg do msg := Ack; end";

  murphi::Designator* des = new murphi::Designator("cache_entry");
  des->addIndex("msg");

  murphi::Alias* a = new murphi::Alias("msg", des);
  murphi::AliasStmt alias(a);

  murphi::Designator* msgDes = new murphi::Designator("msg");
  murphi::Designator* ackDes = new murphi::Designator("Ack");
  murphi::Assignment* ass = new murphi::Assignment(msgDes, ackDes);
  alias.addStatement(ass);

  EXPECT_STREQ(alias.getAsString().c_str(), expectedText.c_str());
}

TEST(StmtSuite, ProcCall) {
  std::string expectedText = "foo(msg)";
  murphi::Designator* des = new murphi::Designator("msg");
  murphi::ProcCall pc("foo", des);
  EXPECT_STREQ(pc.getAsString().c_str(), expectedText.c_str());
}

TEST(StmtSuite, ClearStmt) {
  std::string expectedText = "clear cache_controller";
  murphi::Designator* des = new murphi::Designator("cache_controller");
  murphi::ClearStmt cls(des);
  EXPECT_STREQ(cls.getAsString().c_str(), expectedText.c_str());
}

TEST(StmtSuite, ErrorStmt) {
  std::string expectedText = "error \"crashed\"";
  murphi::ErrorStmt es("crashed");
  EXPECT_STREQ(es.getAsString().c_str(), expectedText.c_str());
}

TEST(StmtSuite, AssertStmt) {
  murphi::Designator* d1 = new murphi::Designator("obj");
  murphi::AssertStmt a(d1, "assert failed");
  EXPECT_STREQ(a.getAsString().c_str(), "assert obj \"assert failed\"");

  murphi::Designator* d2 = new murphi::Designator("tst");
  murphi::AssertStmt b(d2);
  EXPECT_STREQ(b.getAsString().c_str(), "assert tst");
}

TEST(StmtSuite, PutStmt) {
  murphi::Designator* des = new murphi::Designator("cache");
  murphi::PutStmt put(des);
  EXPECT_STREQ(put.getAsString().c_str(), "put cache");

  murphi::PutStmt put2("mystr");
  EXPECT_STREQ(put2.getAsString().c_str(), "put \"mystr\"");
}

TEST(StmtSuite, ReturnStmt) {
  murphi::ReturnStmt rs;
  EXPECT_STREQ(rs.getAsString().c_str(), "return");

  murphi::Designator* des = new murphi::Designator("val");
  murphi::ReturnStmt rv(des);
  EXPECT_STREQ(rv.getAsString().c_str(), "return val");
}

TEST(StmtSuite, UndefineStmt){
  murphi::Designator *des = new murphi::Designator("fwd_network");

  murphi::UndefineStmt undef(des);

  EXPECT_STREQ(undef.getAsString().c_str(), "UNDEFINE( fwd_network )");
}