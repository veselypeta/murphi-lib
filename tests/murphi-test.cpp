#include "murphi.h"
#include <gtest/gtest.h>
#include "models/ConstDecl.h"
#include "models/Expr.h"
#include "models/Formal.h"
#include "models/TypeDecl.h"
#include "models/TypeExpr.h"
#include "models/VarDecl.h"
#include "models/Quantifier.h"
#include "proc/ProcDecl.h"
#include "proc/Statements.h"
#include "utils/PrintUtils.h"

// Test Module is printed correctly
TEST(ModuleSuite, CorrectlyPrinting) {
  murphi::Module m;
  // add NrCaches = 4;
  murphi::Expr* expr = new murphi::IntExpr(4);
  std::string id = "NrCaches";
  m.addConstDecl(id, expr);

  // add a complex constant
  std::string id2 = "complex";
  murphi::Expr* expr2 = new murphi::IntExpr(6);
  murphi::Expr* expr3 = new murphi::IntExpr(5);
  murphi::Expr* expr4 = new murphi::AddExpr(expr2, expr3);
  m.addConstDecl(id2, expr4);

  // add a basic type
  murphi::TypeExpr* texpr = new murphi::ID("idType");
  m.addTypeDecl("myType", texpr);

  // add a basic variable
  murphi::TypeExpr* nTypeExpr = new murphi::ID("OBJSET_cache");
  m.addVarDecl("myVar", nTypeExpr);

  std::string expectedString =
      "\
const \n\
\tNrCaches : 4;\n\
\tcomplex : 6 + 5;\n\
type \n\
\tmyType : idType;\n\
var \n\
\tmyVar : OBJSET_cache;\n\
";

  ASSERT_STREQ(m.getAsString().c_str(), expectedString.c_str());
}

TEST(ModuleSuite, CorrectlyFindsCostDeclReferences) {
  murphi::Module m;
  // add NrCaches = 4;
  murphi::Expr* expr = new murphi::IntExpr(4);
  std::string id = "NrCaches";
  m.addConstDecl(id, expr);

  ASSERT_TRUE(m.isVaidReference(id));
  ASSERT_FALSE(m.isVaidReference("randomReference"));
}

TEST(ModuleSuite, CorrectlyFindsTypeDeclReference) {
  murphi::Module m;
  std::string id = "newType";
  murphi::TypeExpr* typExpr = new murphi::ID(id);
  m.addTypeDecl(id, typExpr);

  ASSERT_TRUE(m.isVaidReference(id));
  ASSERT_FALSE(m.isVaidReference("NrCaches"));
}

// Expressions Suite
TEST(ExprSuite, IntExprPrinting) {
  murphi::Expr* i = new murphi::IntExpr(8);

  ASSERT_STREQ(i->getAsString().c_str(), "8");

  delete i;
}

TEST(ExprSuite, AddExprPrinting) {
  murphi::Expr* i = new murphi::IntExpr(8);
  murphi::Expr* j = new murphi::IntExpr(44);

  murphi::Expr* x = new murphi::AddExpr(i, j);
  ASSERT_STREQ(x->getAsString().c_str(), "8 + 44");

  delete x;
}

TEST(ExprSuite, ParenthExprPrinting) {
  murphi::Expr* i = new murphi::IntExpr(8);
  murphi::Expr* j = new murphi::IntExpr(44);

  murphi::Expr* x = new murphi::AddExpr(i, j);

  murphi::Expr* p = new murphi::ParenthExpr(x);
  ASSERT_STREQ(p->getAsString().c_str(), "(8 + 44)");

  murphi::Expr* next = new murphi::IntExpr(57);
  murphi::Expr* nextAdd = new murphi::AddExpr(p, next);

  ASSERT_STREQ(nextAdd->getAsString().c_str(), "(8 + 44) + 57");

  delete nextAdd;
}

TEST(ExprSuite, SubExprPrinting) {
  murphi::Expr* i = new murphi::IntExpr(8);
  murphi::Expr* j = new murphi::IntExpr(44);

  murphi::Expr* k = new murphi::SubExpr(i, j);
  EXPECT_STREQ(k->getAsString().c_str(), "8 - 44");
  delete k;
}

TEST(ExprSuite, MultExprPrinting) {
  murphi::Expr* i = new murphi::IntExpr(8);
  murphi::Expr* j = new murphi::IntExpr(44);

  murphi::Expr* k = new murphi::MultExpr(i, j);
  EXPECT_STREQ(k->getAsString().c_str(), "8 * 44");

  delete k;
}

TEST(ExprSuite, DivExprPrinting) {
  murphi::Expr* i = new murphi::IntExpr(8);
  murphi::Expr* j = new murphi::IntExpr(44);

  murphi::Expr* k = new murphi::DivExpr(i, j);
  EXPECT_STREQ(k->getAsString().c_str(), "8 / 44");

  delete k;
}

TEST(ExprSuite, RemExprPrinting) {
  murphi::Expr* i = new murphi::IntExpr(8);
  murphi::Expr* j = new murphi::IntExpr(44);

  murphi::Expr* k = new murphi::RemExpr(i, j);
  EXPECT_STREQ(k->getAsString().c_str(), "8 % 44");

  delete k;
}

TEST(ExprSuite, LogNegExprPrinting) {
  murphi::Expr* i = new murphi::IntExpr(8);

  murphi::Expr* k = new murphi::LogNegExpr(i);
  EXPECT_STREQ(k->getAsString().c_str(), "!8");

  delete k;
}

TEST(ExprSuite, LogDisjExprPrinting) {
  murphi::Expr* i = new murphi::IntExpr(8);
  murphi::Expr* j = new murphi::IntExpr(44);

  murphi::Expr* k = new murphi::LogDisjExpr(i, j);
  EXPECT_STREQ(k->getAsString().c_str(), "8 | 44");

  delete k;
}

TEST(ExprSuite, LogConjExprPrinting) {
  murphi::Expr* i = new murphi::IntExpr(8);
  murphi::Expr* j = new murphi::IntExpr(44);

  murphi::Expr* k = new murphi::LogConjExpr(i, j);
  EXPECT_STREQ(k->getAsString().c_str(), "8 & 44");

  delete k;
}

TEST(ExprSuite, LogImplExprPrinting) {
  murphi::Expr* i = new murphi::IntExpr(8);
  murphi::Expr* j = new murphi::IntExpr(44);

  murphi::Expr* k = new murphi::LogImplExpr(i, j);
  EXPECT_STREQ(k->getAsString().c_str(), "8 -> 44");

  delete k;
}

TEST(ExprSuite, LTExprPrinting) {
  murphi::Expr* i = new murphi::IntExpr(8);
  murphi::Expr* j = new murphi::IntExpr(44);

  murphi::Expr* k = new murphi::LTExpr(i, j);
  EXPECT_STREQ(k->getAsString().c_str(), "8 < 44");

  delete k;
}

TEST(ExprSuite, LTEQExprPrinting) {
  murphi::Expr* i = new murphi::IntExpr(8);
  murphi::Expr* j = new murphi::IntExpr(44);

  murphi::Expr* k = new murphi::LTEQExpr(i, j);
  EXPECT_STREQ(k->getAsString().c_str(), "8 <= 44");

  delete k;
}

TEST(ExprSuite, GTExprPrinting) {
  murphi::Expr* i = new murphi::IntExpr(8);
  murphi::Expr* j = new murphi::IntExpr(44);

  murphi::Expr* k = new murphi::GTExpr(i, j);
  EXPECT_STREQ(k->getAsString().c_str(), "8 < 44");

  delete k;
}

TEST(ExprSuite, EQExprPrinting) {
  murphi::Expr* i = new murphi::IntExpr(8);
  murphi::Expr* j = new murphi::IntExpr(44);

  murphi::Expr* k = new murphi::EQExpr(i, j);
  EXPECT_STREQ(k->getAsString().c_str(), "8 = 44");

  delete k;
}

TEST(ExprSuite, NEQExprPrinting) {
  murphi::Expr* i = new murphi::IntExpr(8);
  murphi::Expr* j = new murphi::IntExpr(44);

  murphi::Expr* k = new murphi::NEQExpr(i, j);
  EXPECT_STREQ(k->getAsString().c_str(), "8 != 44");

  delete k;
}

TEST(ExprSuite, CondExprPrinting) {
  murphi::Expr* i = new murphi::IntExpr(8);
  murphi::Expr* j = new murphi::IntExpr(44);
  murphi::Expr* j2 = new murphi::IntExpr(48);

  murphi::Expr* k = new murphi::CondExpr(i, j, j2);
  EXPECT_STREQ(k->getAsString().c_str(), "8 ? 44 : 48");

  delete k;
}

TEST(ExprSuite, GTEQExprPrinting) {
  murphi::Expr* i = new murphi::IntExpr(8);
  murphi::Expr* j = new murphi::IntExpr(44);

  murphi::Expr* k = new murphi::GTEQExpr(i, j);
  EXPECT_STREQ(k->getAsString().c_str(), "8 <= 44");

  delete k;
}

TEST(ConstDeclSuite, PrintConstDecl) {
  murphi::Expr* i = new murphi::IntExpr(8);
  murphi::Expr* j = new murphi::IntExpr(44);

  murphi::Expr* x = new murphi::AddExpr(i, j);

  murphi::Expr* p = new murphi::ParenthExpr(x);

  murphi::ConstDecl* constDecl = new murphi::ConstDecl("tmpSummation", p);

  ASSERT_STREQ(constDecl->getAsString().c_str(), "tmpSummation : (8 + 44);");

  delete constDecl;
}

// Type Expr Suite
TEST(TypeExprSuite, PrintIDTypeExpr) {
  murphi::TypeExpr* a = new murphi::ID("test");
  EXPECT_STREQ(a->getAsString().c_str(), "test");
  delete a;
}

TEST(TypeExprSuite, IntegerSubrangePrint) {
  murphi::Expr* a = new murphi::IntExpr(0);
  murphi::Expr* b = new murphi::IntExpr(5);

  murphi::TypeExpr* c = new murphi::IntegerSubRange(a, b);

  EXPECT_STREQ(c->getAsString().c_str(), "0 .. 5");

  delete c;
}

TEST(TypeExprSuite, EnumPrint) {
  murphi::Enum* e = new murphi::Enum();
  e->addEnum("val1");
  e->addEnum("val2");
  e->addEnum("random");

  EXPECT_STREQ(e->getAsString().c_str(), "enum {val1,val2,random};");

  delete e;
}

TEST(TypeExprSuite, RecordPrint) {
  murphi::Record* r = new murphi::Record();
  murphi::TypeExpr* at = new murphi::ID("test");
  murphi::VarDecl* a = new murphi::VarDecl("init", at);
  r->addVarDecl(a);

  EXPECT_STREQ(r->getAsString().c_str(), "record [init : test;];");

  delete r;
}

// Type Decl tests
TEST(TypeDeclSuite, PrintsIdTypeExpression) {
  // No verification on if 'NrCaches' acutally exists
  std::string tId = "myType";
  murphi::TypeExpr* idTyExpr = new murphi::ID("NrCaches");
  murphi::TypeDecl* tDecl = new murphi::TypeDecl(tId, idTyExpr);

  std::string expected = "myType : NrCaches;";

  EXPECT_STREQ(tDecl->getAsString().c_str(), expected.c_str());

  delete tDecl;
}

// Test Var Decls
TEST(VarDeclSuite, PrintsVarDeclsCorrectly) {
  std::string vId = "cache";
  murphi::TypeExpr* texpr = new murphi::ID("OBJSET_cache");
  murphi::VarDecl* varDecl = new murphi::VarDecl(vId, texpr);

  EXPECT_STREQ(varDecl->getId().c_str(), "cache");
  EXPECT_STREQ(varDecl->getAsString().c_str(), "cache : OBJSET_cache;");

  delete varDecl;
}

// Quantifier //
TEST(QuantifierSuite, BasicQuantifier){
  murphi::IntExpr *start = new murphi::IntExpr(0);
  murphi::IntExpr *end = new murphi::IntExpr(10);
  murphi::IntegerSubRange *range = new murphi::IntegerSubRange(start, end);
  murphi::Quantifier q("i",range);
  EXPECT_STREQ(q.getAsString().c_str(), "i : 0 .. 10");
}

// Utils
TEST(UtilsSuite, Interleave) {
  std::vector<std::string> s = {"hi", "hello", "bob", "plant", "steve"};
  std::string out = murphi::utils::interleave(s, "|");
  EXPECT_STREQ(out.c_str(), "hi|hello|bob|plant|steve");
}
TEST(UtilsSuite, InterleaveOne) {
  std::vector<std::string> s = {"hi"};
  std::string out = murphi::utils::interleave(s, "|");
  EXPECT_STREQ(out.c_str(), "hi");
}

TEST(UtilsSuite, InterleaveComma) {
  std::vector<std::string> s = {"hi", "hello", "bob"};
  std::string out = murphi::utils::interleaveComma(s);
  EXPECT_STREQ(out.c_str(), "hi,hello,bob");
}

// -- Formal --
TEST(FormalSuite, FormalPrint) {
  murphi::TypeExpr* t = new murphi::ID("cache");
  murphi::Formal* f = new murphi::Formal("myIdent", t);

  EXPECT_STREQ(f->getAsString().c_str(), "var myIdent : cache");

  delete f;
}

// -- Designator --
TEST(DesignatorSuite, FieldPrint) {
  murphi::Designator d("cache");
  d.addIndex("cl");
  d.addIndex("val");
  EXPECT_STREQ(d.getAsString().c_str(), "cache.cl.val");
}

TEST(DesignatorSuite, IndexPrint) {
  murphi::Designator* d = new murphi::Designator("cache");
  murphi::Expr* intExpr = new murphi::IntExpr(8);
  d->addIndex(intExpr);
  murphi::Expr* dn = new murphi::Designator("val");
  d->addIndex(dn);
  EXPECT_STREQ(d->getAsString().c_str(), "cache[8][val]");

  delete d;
  delete intExpr;
  delete dn;
}

TEST(DesignatorSuite, MixPrint) {
  murphi::Designator d("cache");
  d.addIndex("cl");
  murphi::Expr* x = new murphi::Designator("i");
  d.addIndex(x);

  EXPECT_STREQ(d.getAsString().c_str(), "cache.cl[i]");
}

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

TEST(StmtSuite, ForStmt){
  // generate the range to loop over
  murphi::IntExpr *start = new murphi::IntExpr(0);
  murphi::IntExpr *end = new murphi::IntExpr(10);
  murphi::IntegerSubRange *range = new murphi::IntegerSubRange(start, end);
  murphi::Quantifier *q = new murphi::Quantifier("i",range); 

  murphi::ForStmt forStmt(q);

  // add some statements
  murphi::Designator *des = new murphi::Designator("cache_entry");
  des->addIndex("State");
  murphi::Designator *rhs = new murphi::Designator("I_load");
  murphi::Assignment *as = new murphi::Assignment(des, rhs);

  forStmt.addStatement(as);

  EXPECT_STREQ(forStmt.getAsString().c_str(), "for i : 0 .. 10 do cache_entry.State := I_load; endfor");

}
