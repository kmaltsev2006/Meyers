/**
 * @brief Prefer auto to explicit type declarations
 *
 */
#include <vector>

#include "../../common.hpp"

void foo(auto callback) { callback(); }

void defaultCallback() {}

int main() {
    std::vector<int> v;
    unsigned int sz1 = v.size();
    auto sz2 = v.size();
    std::cout << sizeof(sz1) << " " << sizeof(sz2) << std::endl;

    auto lambda = [] {};

    foo(lambda);
    foo(defaultCallback);
}