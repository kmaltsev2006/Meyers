/**
 * @brief Type of param is not a reference
 *
 * Think about it as: template always 'eats' references, than reference
 * collapsing rules are applied
 */
#include "../../common.hpp"

template <typename T>
void foo(T param) {
    printTypeCE<decltype(param)>();
}

int main() {
    int x{};
    const int cx{x};
    const int& rx{x};

    foo(x);  // error: use of deleted function ‘void printTypeCE() [with T = int]’
    foo(cx); // error: use of deleted function ‘void printTypeCE() [with T = int]’
    foo(rx); // error: use of deleted function ‘void printTypeCE() [with T = int]’
}