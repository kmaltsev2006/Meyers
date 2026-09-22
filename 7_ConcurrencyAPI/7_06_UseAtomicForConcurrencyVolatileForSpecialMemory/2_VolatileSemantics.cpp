/**
 * @brief Volatile semantics
 *
 */
#include "../../common.hpp"

int main() {
    volatile int x = 42;
    // int x = 42;
    x = 32;
    int w = -10; // ignored by compiler anyway -O3
    auto y = x;
    w = 10; // ignored by compiler anyway -O3
    y = x;
    return y;
}