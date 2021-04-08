#pragma once
#include <string>
#include <vector>

namespace murphi {
namespace utils {

std::string interleave(std::vector<std::string> ins, std::string separator);
std::string interleaveComma(std::vector<std::string> ins);
}  // namespace utils

}  // namespace murphi