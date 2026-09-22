/**
 * @brief Functions taking universal references are the greediest functions in
 * C++
 *
 */

#include "../../common.hpp"

template <typename T>
void foo(T&&) {
    PRINT_CALL();
}

void foo(int) { PRINT_CALL(); }

int main() {
    foo(bool{});
    foo(int{});
    foo(int8_t{});
}