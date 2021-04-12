#include <gtest/gtest.h>
#include "models/ConstDecl.h"
#include "models/Expr.h"
#include "models/Formal.h"
#include "models/Quantifier.h"
#include "models/TypeDecl.h"
#include "models/TypeExpr.h"
#include "models/VarDecl.h"
#include "murphi.h"
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
const NrCaches : 4; \
const complex : 6 + 5; \
type myType : idType; \
var myVar : OBJSET_cache;\
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
