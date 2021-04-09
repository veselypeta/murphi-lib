#pragma once
#include "interfaces/Printable.h"
#include <string>
#include <vector>

namespace murphi {
class Stmt : public Printable<Stmt> {
public:
  virtual std::string getAsString() = 0;
};

// <assignment> ::= <designator> := <expression>
class Assignment : public Stmt {

};

class Stmts : public Printable<Stmts> {
public:
  std::string getAsString();

private:
  std::vector<Stmt> stmts;
};
} // namespace murphi
