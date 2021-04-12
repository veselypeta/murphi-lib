#include <gtest/gtest.h>
#include "models/Decl.h"

TEST(DeclsSuite, DeclPrint) {
  murphi::Decls dec;
  EXPECT_STREQ(dec.getAsString().c_str(), "");
}