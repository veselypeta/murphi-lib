#include "models/ConstDecl.h"
#include "models/Expr.h"
#include "models/TypeDecl.h"
#include "murphi.h"
#include <gtest/gtest.h>

// Test Module is printed correctly
TEST(ModuleSuite, CorrectlyPrinting) {
  murphi::Module m;
  // add NrCaches = 4;
  murphi::Expr *expr = new murphi::IntExpr(4);
  std::string id = "NrCaches";
  m.addConstDecl(id, expr);

  // add a complex constant
  std::string id2 = "complex";
  murphi::Expr *expr2 = new murphi::IntExpr(6);
  murphi::Expr *expr3 = new murphi::IntExpr(5);
  murphi::Expr *expr4 = new murphi::AddExpr(expr2, expr3);
  m.addConstDecl(id2, expr4);

  // add a basic type
  murphi::TypeExpr *texpr = new murphi::IdTypeExpr("idType");
  m.addTypeDecl("myType", texpr);

  std::string expectedString = "\
const \n\
\tNrCaches : 4;\n\
\tcomplex : 6 + 5;\n\
type \n\
\tmyType : idType;\n\
";

  ASSERT_STREQ(m.getAsString().c_str(), expectedString.c_str());
}

TEST(ModuleSuite, CorrectlyFindsCostDeclReferences) {
  murphi::Module m;
  // add NrCaches = 4;
  murphi::Expr *expr = new murphi::IntExpr(4);
  std::string id = "NrCaches";
  m.addConstDecl(id, expr);

  ASSERT_TRUE(m.isVaidReference(id));
  ASSERT_FALSE(m.isVaidReference("randomReference"));
}

TEST(ModuleSuite, CorrectlyFindsTypeDeclReference) {
  murphi::Module m;
  std::string id = "newType";
  murphi::TypeExpr *typExpr = new murphi::IdTypeExpr(id);
  m.addTypeDecl(id, typExpr);

  ASSERT_TRUE(m.isVaidReference(id));
  ASSERT_FALSE(m.isVaidReference("NrCaches"));
}

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

  ASSERT_STREQ(constDecl->getAsString().c_str(), "tmpSummation : (8 + 44);");

  delete constDecl;
}

// Type Decl tests
TEST(TypeDeclSuite, PrintsIdTypeExpression) {

  // No verification on if 'NrCaches' acutally exists
  std::string tId = "myType";
  murphi::TypeExpr *idTyExpr = new murphi::IdTypeExpr("NrCaches");
  murphi::TypeDecl *tDecl = new murphi::TypeDecl(tId, idTyExpr);

  std::string expected = "myType : NrCaches;";

  EXPECT_STREQ(tDecl->getAsString().c_str(), expected.c_str());

  delete tDecl;
}
