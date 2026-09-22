/**
 * @brief decltype(auto)
 *
 */
#include <utility>

#include "../../common.hpp"

int x;
int& rx{x};

decltype(auto) baz() { return rx; }

template <typename T>
decltype(auto) doe(T&& val) {
    return std::forward<T>(val);
}

/*
template<typename T>
auto doe(T&& val) -> decltype(std::forward<T>(val)) {
    return std::forward<T>(val);
}
*/

int main() {
    auto& r = baz();
    r = 42;
    std::cout << x << std::endl;

    printTypeCE<decltype(baz)>();

    int y{};
    printTypeCE<decltype(doe(y))>();
    printTypeCE<decltype(doe(int{}))>();
}