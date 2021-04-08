#include "utils/PrintUtils.h"
#include <string>
#include <vector>
#include <sstream>

namespace murphi {
namespace utils {
    std::string interleave(std::vector<std::string> ins, std::string separator){
        std::string tmp;
        std::string s;
        for (auto x : ins){
            s += tmp;
            s += x;
            tmp = separator;
        }
        return s;
    }


    std::string interleaveComma(std::vector<std::string> ins){
        return interleave(ins, ",");
    }
} // namespace util
} // namespace murphi
