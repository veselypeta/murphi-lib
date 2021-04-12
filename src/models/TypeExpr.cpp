#include "models/TypeExpr.h"
#include <string>
#include "models/VarDecl.h"
#include "utils/PrintUtils.h"

namespace murphi {
std::string ID::getAsString() {
  return typeId;
}

std::string IntegerSubRange::getAsString() {
  return lhs->getAsString() + " .. " + rhs->getAsString();
}

std::string Enum::getAsString() {
  return "enum {" + utils::interleaveComma(es) + "}";
}

void Enum::addEnum(std::string enumValue) {
  es.push_back(enumValue);
}

std::string Record::getAsString() {
  std::string s = "record";
  for (auto vd : body) {
    s += " " + vd->getAsString() + ";";
  }
  return s;
}

void Record::addVarDecl(VarDecl* vd) {
  body.push_back(vd);
}
}  // namespace murphi
