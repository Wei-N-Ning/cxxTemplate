#include <functional>
#include <vector>
#include <cassert>

int main() {
    std::function<double(std::vector<double>)> func = 
        [](std::vector<double> vd) -> double {
            double result = 0;
            for (const auto& elem : vd) {
                result += elem;
            }
            return result;
        };
    assert(3 == func({1, 2}));
    return 0;
}
