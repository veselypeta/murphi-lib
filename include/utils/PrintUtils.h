#pragma once
#include <string>
#include <vector>
#include "models/Expr.h"

namespace murphi::utils {

std::string interleave(std::vector<std::string> ins, std::string separator);
std::string interleaveComma(std::vector<std::string> ins);
std::string interleaveComma(std::vector<Expr*> ins);
}  // namespace murphi