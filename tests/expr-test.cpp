#include "models/Expr.h"
#include <gtest/gtest.h>
#include "models/ConstDecl.h"
#include "models/Formal.h"
#include "models/Quantifier.h"
#include "models/VarDecl.h"

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

  ASSERT_STREQ(constDecl->getAsString().c_str(), "tmpSummation : (8 + 44)");

  delete constDecl;
}

// Test Var Decls
TEST(VarDeclSuite, PrintsVarDeclsCorrectly) {
  std::string vId = "cache";
  murphi::TypeExpr* texpr = new murphi::ID("OBJSET_cache");
  murphi::VarDecl* varDecl = new murphi::VarDecl(vId, texpr);

  EXPECT_STREQ(varDecl->getId().c_str(), "cache");
  EXPECT_STREQ(varDecl->getAsString().c_str(), "cache : OBJSET_cache");

  delete varDecl;
}

// Quantifier //
TEST(QuantifierSuite, BasicQuantifier) {
  murphi::IntExpr* start = new murphi::IntExpr(0);
  murphi::IntExpr* end = new murphi::IntExpr(10);
  murphi::IntegerSubRange* range = new murphi::IntegerSubRange(start, end);
  murphi::Quantifier q("i", range);
  EXPECT_STREQ(q.getAsString().c_str(), "i : 0 .. 10");
}

// -- Formal --
TEST(FormalSuite, FormalPrint) {
  murphi::TypeExpr* t = new murphi::ID("cache");
  murphi::Formal* f = new murphi::Formal("myIdent", t);

  EXPECT_STREQ(f->getAsString().c_str(), "var myIdent : cache");

  delete f;
}
