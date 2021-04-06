#include "murphi.h"
#include "models/Expr.h"
#include <gtest/gtest.h>

// Test module is created without error
TEST(MurphiSuite, CreateModuleObject) { murphi::Module mod; }

// Expressions Suite
TEST(ExprSuite, IntExprPrinting) {
  murphi::Expr *i = new murphi::IntExpr(8);

  ASSERT_STREQ(i->getAsString().c_str(), "8");

  delete i;
}

TEST(ExprSuite, AddExprPrinting) {
  murphi::Expr *i = new murphi::IntExpr(8);
  murphi::Expr *j = new murphi::IntExpr(44);

  murphi::Expr *x = new murphi::AddExpr(i, j);
  ASSERT_STREQ(x->getAsString().c_str(), "8 + 44");

  delete x;
}

TEST(ExprSuite, ParenthExprPrinting) {
  murphi::Expr *i = new murphi::IntExpr(8);
  murphi::Expr *j = new murphi::IntExpr(44);

  murphi::Expr *x = new murphi::AddExpr(i, j);

  murphi::Expr *p = new murphi::ParenthExpr(x);
  ASSERT_STREQ(p->getAsString().c_str(), "(8 + 44)");

  delete p;
}
