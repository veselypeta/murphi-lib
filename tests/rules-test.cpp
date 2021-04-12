#include "rules/rules.h"
#include <gtest/gtest.h>

TEST(RulesSuite, SimpleRulePrint) {
  std::string expectedText =
      "rule \"cache_I_load\" ==> begin SEND_cache_I_load(adr, m) end";
  // create a rule expr
  murphi::Designator *des = new murphi::Designator("cache");
  des->addIndex("State");
  murphi::Designator *desState = new murphi::Designator("cache_I");
  murphi::EQExpr *rulExp = new murphi::EQExpr(des, desState);

  murphi::SimpleRule sr("myRule", rulExp);

  // generate the stmt
  murphi::Designator *firstArg = new murphi::Designator("adr");
  murphi::Designator *secondArg = new murphi::Designator("m");
  murphi::ProcCall *procCallStmt =
      new murphi::ProcCall("SEND_cache_I_load", firstArg);
  procCallStmt->addArgument(secondArg);

  sr.statements.addStatement(procCallStmt);

  EXPECT_STREQ(sr.getAsString().c_str(), expectedText.c_str());
}