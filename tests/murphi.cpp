#include "murphi.h"
#include "models/ConstDecl.h"
#include "models/Expr.h"
#include <gtest/gtest.h>

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

  murphi::Expr *next = new murphi::IntExpr(57);
  murphi::Expr *nextAdd = new murphi::AddExpr(p, next);

  ASSERT_STREQ(nextAdd->getAsString().c_str(), "(8 + 44) + 57");


  delete nextAdd;
}

TEST(ConstDeclSuite, PrintConstDecl) {
  murphi::Expr *i = new murphi::IntExpr(8);
  murphi::Expr *j = new murphi::IntExpr(44);

  murphi::Expr *x = new murphi::AddExpr(i, j);

  murphi::Expr *p = new murphi::ParenthExpr(x);

  murphi::ConstDecl *constDecl = new murphi::ConstDecl("tmpSummation", p);

  ASSERT_STREQ(constDecl->getAsString().c_str(), "tmpSummation : (8 + 44)");

  delete constDecl;
}
