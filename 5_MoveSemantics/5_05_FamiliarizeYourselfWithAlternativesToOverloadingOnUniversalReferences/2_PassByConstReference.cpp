/**
 * @brief Pass by const T&
 *
 */

#include "../../common.hpp"

void foo(const bool&) { PRINT_CALL(); }

void foo(int) { PRINT_CALL(); }

int main() {
    bool b;
    foo(b);

    int i;
    foo(i);

    int8_t i8;
    foo(i8);
}