#include "utils/PrintUtils.h"
#include <sstream>
#include <string>
#include <vector>
#include "models/Expr.h"

namespace murphi {
namespace utils {
std::string interleave(std::vector<std::string> ins, std::string separator) {
  std::string tmp;
  std::string s;
  for (auto x : ins) {
    s += tmp;
    s += x;
    tmp = separator;
  }
  return s;
}

std::string interleaveComma(std::vector<std::string> ins) {
  return interleave(ins, ",");
}

std::string interleaveComma(std::vector<Expr*> ins) {
  std::vector<std::string> val;
  for (auto i : ins) {
    val.push_back(i->getAsString());
  }
  return interleaveComma(val);
}
}  // namespace utils
}  // namespace murphi
