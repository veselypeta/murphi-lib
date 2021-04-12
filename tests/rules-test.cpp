#include "models/ConstDecl.h"
#include "models/Quantifier.h"
#include "models/TypeExpr.h"
#include "proc/Statements.h"
#include "rules/rules.h"
#include <gtest/gtest.h>

TEST(RulesSuite, SimpleRulePrint) {
  std::string expectedText = "rule \"cache_I_load\" cache.State = cache_I ==>  "
                             "begin SEND_cache_I_load(adr,m); end";
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

TEST(RulesSuite, StartStatePrint) {

  murphi::StartState ss("initialization");
  EXPECT_STREQ(ss.getAsString().c_str(),
               "startstate \"initialization\"  begin  end");

  // add a statement
  murphi::Designator *lhs = new murphi::Designator("cache");
  lhs->addIndex("State");
  murphi::Designator *rhs = new murphi::Designator("cache_I");
  murphi::Assignment *ass = new murphi::Assignment(lhs, rhs);

  ss.statements.addStatement(ass);

  EXPECT_STREQ(
      ss.getAsString().c_str(),
      "startstate \"initialization\"  begin cache.State := cache_I; end");

  // add a decl
  murphi::IntExpr *maxVal = new murphi::IntExpr(7);
  murphi::ConstDecl *cd = new murphi::ConstDecl("maxValue", maxVal);
  ss.decls.addDecl(cd);

  EXPECT_STREQ(ss.getAsString().c_str(),
               "startstate \"initialization\" const maxValue : 7; begin "
               "cache.State := cache_I; end");
}

TEST(RuleSuite, InvariantPrint) {

  murphi::Designator *des = new murphi::Designator("cache");
  des->addIndex("State");
  murphi::Designator *st = new murphi::Designator("cache_I");
  murphi::EQExpr *eq = new murphi::EQExpr(des, st);

  murphi::Invariant inv("Write Serialization", eq);

  EXPECT_STREQ(inv.getAsString().c_str(),
               "invariant \"Write Serialization\" cache.State = cache_I");
}

TEST(RuleSuite, InvariantPrintWOName) {

  murphi::Designator *des = new murphi::Designator("cache");
  des->addIndex("State");
  murphi::Designator *st = new murphi::Designator("cache_I");
  murphi::EQExpr *eq = new murphi::EQExpr(des, st);

  murphi::Invariant inv(eq);

  EXPECT_STREQ(inv.getAsString().c_str(),
               "invariant \"\" cache.State = cache_I");
}

TEST(RuleSuite, RuleSetPrint) {
  /*
  ruleset m:OBJSET_cache do

  end
  */
  murphi::ID *id = new murphi::ID("OBJSET_cache");
  murphi::Quantifier *q = new murphi::Quantifier("m", id);
  murphi::RuleSet rs(q);

  EXPECT_STREQ(rs.getAsString().c_str(), "ruleset m : OBJSET_cache do  end");

  // create a rule expr
  murphi::Designator *des = new murphi::Designator("cache");
  des->addIndex("State");
  murphi::Designator *desState = new murphi::Designator("cache_I");
  murphi::EQExpr *rulExp = new murphi::EQExpr(des, desState);

  murphi::SimpleRule *sr = new murphi::SimpleRule("cache_I_load", rulExp);

  // generate the stmt
  murphi::Designator *firstArg = new murphi::Designator("adr");
  murphi::Designator *secondArg = new murphi::Designator("m");
  murphi::ProcCall *procCallStmt =
      new murphi::ProcCall("SEND_cache_I_load", firstArg);
  procCallStmt->addArgument(secondArg);

  sr->statements.addStatement(procCallStmt);

  rs.addRule(sr);

  EXPECT_STREQ(rs.getAsString().c_str(),
               "ruleset m : OBJSET_cache do rule \"cache_I_load\" cache.State "
               "= cache_I ==>  begin SEND_cache_I_load(adr,m); end; end");
}

TEST(RuleSuite, AliasRulePrint) {

  murphi::Designator *aldes = new murphi::Designator("i_cache");
  murphi::Designator *m = new murphi::Designator("m");
  aldes->addIndex(m);

  murphi::Alias *ali = new murphi::Alias("cle", aldes);

  murphi::AliasRule ar(ali);

  EXPECT_STREQ(ar.getAsString().c_str(), "alias cle : i_cache[m] do  end");

  // create a rule expr
  murphi::Designator *des = new murphi::Designator("cache");
  des->addIndex("State");
  murphi::Designator *desState = new murphi::Designator("cache_I");
  murphi::EQExpr *rulExp = new murphi::EQExpr(des, desState);

  murphi::SimpleRule *sr = new murphi::SimpleRule("cache_I_load", rulExp);
  // generate the stmt
  murphi::Designator *firstArg = new murphi::Designator("adr");
  murphi::Designator *secondArg = new murphi::Designator("m");
  murphi::ProcCall *procCallStmt =
      new murphi::ProcCall("SEND_cache_I_load", firstArg);
  procCallStmt->addArgument(secondArg);

  sr->statements.addStatement(procCallStmt);

  ar.addRule(sr);

  EXPECT_STREQ(ar.getAsString().c_str(),
               "alias cle : i_cache[m] do rule \"cache_I_load\" cache.State "
               "= cache_I ==>  begin SEND_cache_I_load(adr,m); end; end");
}
