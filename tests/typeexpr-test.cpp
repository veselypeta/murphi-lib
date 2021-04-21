#include "models/TypeDecl.h"
#include "models/TypeExpr.h"
#include "models/VarDecl.h"
#include "models/Expr.h"
#include <gtest/gtest.h>

// Type Expr Suite
TEST(TypeExprSuite, PrintIDTypeExpr) {
  murphi::TypeExpr *a = new murphi::ID("test");
  EXPECT_STREQ(a->getAsString().c_str(), "test");
  delete a;
}

TEST(TypeExprSuite, IntegerSubrangePrint) {
  murphi::Expr *a = new murphi::IntExpr(0);
  murphi::Expr *b = new murphi::IntExpr(5);

  murphi::TypeExpr *c = new murphi::IntegerSubRange(a, b);

  EXPECT_STREQ(c->getAsString().c_str(), "0 .. 5");

  delete c;
}

TEST(TypeExprSuite, EnumPrint) {
  murphi::Enum *e = new murphi::Enum();
  e->addEnum("val1");
  e->addEnum("val2");
  e->addEnum("random");

  EXPECT_STREQ(e->getAsString().c_str(), "enum {val1,val2,random}");

  delete e;
}

TEST(TypeExprSuite, RecordPrint) {
  murphi::Record *r = new murphi::Record();
  murphi::TypeExpr *at = new murphi::ID("test");
  murphi::VarDecl *a = new murphi::VarDecl("init", at);
  r->addVarDecl(a);

  EXPECT_STREQ(r->getAsString().c_str(), "record init : test;");

  delete r;
}

// Type Decl tests
TEST(TypeDeclSuite, PrintsIdTypeExpression) {
  // No verification on if 'NrCaches' acutally exists
  std::string tId = "myType";
  murphi::TypeExpr *idTyExpr = new murphi::ID("NrCaches");
  murphi::TypeDecl *tDecl = new murphi::TypeDecl(tId, idTyExpr);

  std::string expected = "myType : NrCaches";

  EXPECT_STREQ(tDecl->getAsString().c_str(), expected.c_str());

  delete tDecl;
}

// SCALARSET TEST
TEST(TypeExprSuite, ScalarSetPrint) {
  murphi::Designator *des = new murphi::Designator("caches");

  murphi::ScalarSet ss(des);

  EXPECT_STREQ(ss.getAsString().c_str(), "SCALARSET( caches )");
}

// UNION TEST
TEST(TypeExprSuite, UnionPrintTest) {

  murphi::Union un("first", "second");

  EXPECT_STREQ(un.getAsString().c_str(), "UNION{first,second}");

  un.addElem("third");
  EXPECT_STREQ(un.getAsString().c_str(), "UNION{first,second,third}");
  un.addElem("fourth");
  EXPECT_STREQ(un.getAsString().c_str(), "UNION{first,second,third,fourth}");
}