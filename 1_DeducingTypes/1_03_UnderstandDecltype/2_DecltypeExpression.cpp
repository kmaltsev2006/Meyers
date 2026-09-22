/**
 * @brief decltype
 *
 */
#include "../../common.hpp"

int main() {
    int x{};
    int& rx{x};
    decltype(rx) y;

    printTypeCE<decltype(y)>();
}