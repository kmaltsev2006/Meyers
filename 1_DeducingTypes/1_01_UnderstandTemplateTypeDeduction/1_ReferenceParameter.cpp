/**
 * @brief Type of param is reference
 *
 */
#include "../../common.hpp"

template <typename T>
void foo(T& param) {
    printTypeCE<decltype(param)>();
}

int main() {
    int x{};
    const int cx{x};
    const int& rx{x};

    foo(x);  // error: use of deleted function ‘void printTypeCE() [with T = int&]’
    foo(cx); // error: use of deleted function ‘void printTypeCE() [with T = const
             // int&]’
    foo(rx); // error: use of deleted function ‘void printTypeCE() [with T = const
             // int&]’
}