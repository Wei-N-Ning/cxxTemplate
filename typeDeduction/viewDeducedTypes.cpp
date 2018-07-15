//
// Created by wein on 5/26/18.
//

#include <map>
#include <vector>
#include <string>

template<typename T>
class TD;  // type display tool

template<typename T>
void someF(const T &param) {
    // To use the type display tool
    //
    // TD<const std::map<
    //   std::__cxx11::basic_string<char>,
    //   std::vector<
    //      std::__cxx11::basic_string<char>
    //   >
    // >&> x
    // TD<decltype(param)> x;
}

int main() {
    std::map<std::string, std::vector<std::string>> m;
    someF(m);
    return 0;
}
