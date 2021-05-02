#pragma once
#include <string>

namespace murphi {
template <class T>
class Printable {
 public:
  virtual std::string getAsString() { return getAsString(); };
  // TODO -- include print() -> to osstream
};

}  // namespace murphi
