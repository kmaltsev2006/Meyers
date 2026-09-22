/**
 * @brief Prefer nullptr to 0 and NULL
 *
 */
#include "../../common.hpp"

void foo(int*) { PRINT_CALL(); }

void foo(int) { PRINT_CALL(); }

#define NILL 0

int main() {
    foo(nullptr);
    foo(NILL);
}