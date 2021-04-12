#include <gtest/gtest.h>
#include "models/Expr.h"

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
