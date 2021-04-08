#include "murphi.h"
#include <gtest/gtest.h>
#include "models/ConstDecl.h"
#include "models/Expr.h"
#include "models/TypeDecl.h"
#include "models/TypeExpr.h"
#include "models/VarDecl.h"
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

// Utils

TEST(UtilsSuite, Interleave) {
  std::vector<std::string> s = {"hi", "hello", "bob", "plant", "steve"};
  std::string out = murphi::utils::interleave(s, "|");
  EXPECT_STREQ(out.c_str(), "hi|hello|bob|plant|steve");
}

TEST(UtilsSuite, InterleaveComma) {
  std::vector<std::string> s = {"hi", "hello", "bob"};
  std::string out = murphi::utils::interleaveComma(s);
  EXPECT_STREQ(out.c_str(), "hi,hello,bob");
}