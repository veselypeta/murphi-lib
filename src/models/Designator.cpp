#include "models/Designator.h"
#include <string>

namespace murphi {

std::string Designator::getAsString() {
    std::string s = id;
    for (Container idx : indexes){
        s += idx.getAsString();
    }
    return s;
}

void Designator::addIndex(std::string fieldId) {
    indexes.push_back(Container(fieldId));
}

void Designator::addIndex(Expr *arrayIndx) {
    indexes.push_back(Container(arrayIndx));
}

} // namespace murphi
