#pragma once
#include <string>
namespace murphi {
template <class T>
class Identifyable {
 public:
  [[nodiscard]] std::string getId() const { return getId(); };
};

}  // namespace murphi
