/**
 * @brief Functions as arguments
 *
 * Useless...
 */
#include "../../common.hpp"

void foo() {}

template <typename T>
void bar1(T param) {
    printTypeCE<decltype(param)>();
}

template <typename T>
void bar2(T& param) {
    printTypeCE<decltype(param)>();
}

int main() {
    bar1(foo); // error: use of deleted function ‘void printTypeCE() [with T = void
               // (*)()]’
    bar2(foo); // error: use of deleted function ‘void printTypeCE() [with T = void
               // (&)()]’
}