/**
 * @brief Array arguments
 *
 * T[] is T* for compilers
 */
#include "../../common.hpp"

void foo(int[]) { PRINT_CALL(); }

// void foo(int*) {} // error: redefinition of ‘void foo(int*)’

int main() {
    constexpr size_t kSz{42};
    int arr[kSz]{};
    foo(arr);
}