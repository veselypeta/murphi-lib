#include "rules/rules.h"
#include "models/ConstDecl.h"
#include <gtest/gtest.h>

TEST(RulesSuite, SimpleRulePrint) {
  std::string expectedText =
      "rule \"cache_I_load\" cache.State = cache_I ==>  begin SEND_cache_I_load(adr,m); end";
  // create a rule expr
  murphi::Designator *des = new murphi::Designator("cache");
  des->addIndex("State");
  murphi::Designator *desState = new murphi::Designator("cache_I");
  murphi::EQExpr *rulExp = new murphi::EQExpr(des, desState);

  murphi::SimpleRule sr("cache_I_load", rulExp);

  // generate the stmt
  murphi::Designator *firstArg = new murphi::Designator("adr");
  murphi::Designator *secondArg = new murphi::Designator("m");
  murphi::ProcCall *procCallStmt =
      new murphi::ProcCall("SEND_cache_I_load", firstArg);
  procCallStmt->addArgument(secondArg);

  sr.statements.addStatement(procCallStmt);

  EXPECT_STREQ(sr.getAsString().c_str(), expectedText.c_str());
}

TEST(RulesSuite, StartStatePrint){
  
  murphi::StartState ss("initialization");
  EXPECT_STREQ(ss.getAsString().c_str(), "startstate \"initialization\"  begin  end");

  // add a statement
  murphi::Designator *lhs = new murphi::Designator("cache");
  lhs->addIndex("State");
  murphi::Designator *rhs = new murphi::Designator("cache_I");
  murphi::Assignment *ass = new murphi::Assignment(lhs, rhs);

  ss.statements.addStatement(ass);

  EXPECT_STREQ(ss.getAsString().c_str(), "startstate \"initialization\"  begin cache.State := cache_I; end");

  // add a decl
  murphi::IntExpr *maxVal = new murphi::IntExpr(7);
  murphi::ConstDecl *cd = new murphi::ConstDecl("maxValue", maxVal);
  ss.decls.addDecl(cd);

  EXPECT_STREQ(ss.getAsString().c_str(), "startstate \"initialization\" const maxValue : 7; begin cache.State := cache_I; end");
}