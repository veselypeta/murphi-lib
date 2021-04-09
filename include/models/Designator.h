#pragma once
#include "interfaces/Printable.h"
#include "models/Expr.h"
#include <string>
#include <vector>

namespace murphi {
// <designator> :=	<ID> { . <ID> | \[ <expr> \] }
// i.e. msg.src or cl[index]
class Designator : Printable<Designator> {
public:
  Designator(std::string id) : id{id} {}
  std::string getAsString();
  void addIndex(std::string fieldId);
  void addIndex(Expr *arrIndex);

private:
  typedef enum { ID, EXPR } identOrExpr;
  class Container {
  public:
    Container(std::string fieldId) : fieldId{fieldId}, type{ID} {}
    Container(Expr *expr) : expr{expr}, type{EXPR} {}
    std::string getAsString() {
        if(type == ID){
            return "." + fieldId;
        } else {
            return "[" + expr->getAsString() + "]";
        }
    }

  private:
    std::string fieldId;
    Expr *expr;
    identOrExpr type;
  };
  std::string id;
  std::vector<Container> indexes;
};
} // namespace murphi
