/**
 * @brief Type of param is universal (forwarding) reference
 *
 * Reference collapsing:
 * & & -> &
 * & && -> &
 * && & -> &
 * && && -> &&
 *
 * Additional:
 * T T& -> T
 * T T&& -> T
 */
#include "../../common.hpp"

template <typename T>
void foo(T&& param) {
    printTypeCE<decltype(param)>();
}

int main() {
    int x{};

    foo(x);     // error: use of deleted function ‘void printTypeCE() [with T = int&]’
    foo(int{}); // error: use of deleted function ‘void printTypeCE() [with T =
                // int&&]’
}