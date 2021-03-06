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

Record::Record(const Record& rhs) {
  for (std::vector<VarDecl*>::const_iterator it = rhs.body.begin();
       it != rhs.body.end(); ++it) {
    body.push_back((*it)->clone());
  }
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

std::string ScalarSet::getAsString() {
  return "SCALARSET( " + expr->getAsString() + " )";
}

std::string Union::getAsString() {
  return "UNION{" + utils::interleaveComma(elems) + "}";
}

// multisettype	: MULTISET "[" expr "]" OF typeExpr
std::string MultiSet::getAsString() {
  return "MULTISET [" + expr->getAsString() + "] OF " + tyExpr->getAsString();
}

}  // namespace murphi
