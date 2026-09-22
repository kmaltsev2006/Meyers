/**
 * @brief Abandon overloading
 *
 */

#include "../../common.hpp"

template <typename T>
void foo(T&&) {
    PRINT_CALL();
}

void bar(int) { PRINT_CALL(); }

int main() {
    foo(bool{});
    bar(int{});
    bar(int8_t{});
}