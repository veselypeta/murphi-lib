#include "murphi.h"
#include <gtest/gtest.h>
#include "models/ConstDecl.h"
#include "models/Expr.h"

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

  std::string expectedString =
      "\
const \n\
\tNrCaches : 4;\n\
\tcomplex : 6 + 5;\n\
";

  ASSERT_STREQ(m.getAsString().c_str(), expectedString.c_str());
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

TEST(ConstDeclSuite, PrintConstDecl) {
  murphi::Expr* i = new murphi::IntExpr(8);
  murphi::Expr* j = new murphi::IntExpr(44);

  murphi::Expr* x = new murphi::AddExpr(i, j);

  murphi::Expr* p = new murphi::ParenthExpr(x);

  murphi::ConstDecl* constDecl = new murphi::ConstDecl("tmpSummation", p);

  ASSERT_STREQ(constDecl->getAsString().c_str(), "tmpSummation : (8 + 44);");

  delete constDecl;
}
