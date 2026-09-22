/**
 * @brief Trailing return type
 *
 */
#include "../../common.hpp"

int x;
int& rx = x;

auto foo() { return x; }

auto bar() -> int { return rx; }

int main() {
    printTypeCE<decltype(foo)>();
    printTypeCE<decltype(bar)>();
}