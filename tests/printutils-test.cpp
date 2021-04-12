#include "utils/PrintUtils.h"
#include <gtest/gtest.h>

// Utils
TEST(UtilsSuite, Interleave) {
  std::vector<std::string> s = {"hi", "hello", "bob", "plant", "steve"};
  std::string out = murphi::utils::interleave(s, "|");
  EXPECT_STREQ(out.c_str(), "hi|hello|bob|plant|steve");
}
TEST(UtilsSuite, InterleaveOne) {
  std::vector<std::string> s = {"hi"};
  std::string out = murphi::utils::interleave(s, "|");
  EXPECT_STREQ(out.c_str(), "hi");
}

TEST(UtilsSuite, InterleaveComma) {
  std::vector<std::string> s = {"hi", "hello", "bob"};
  std::string out = murphi::utils::interleaveComma(s);
  EXPECT_STREQ(out.c_str(), "hi,hello,bob");
}