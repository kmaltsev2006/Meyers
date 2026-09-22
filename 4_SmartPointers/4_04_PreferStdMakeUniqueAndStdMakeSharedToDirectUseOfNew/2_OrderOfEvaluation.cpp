/**
 * @brief OER (Order Of Evaluation Rule)
 *
 */
#include "../../common.hpp"

#include <memory>

int main() {
    static auto foo = [](std::unique_ptr<int>, int) {};

    foo(std::unique_ptr<int>(new int{}), int{}); // potential UB: memory leak (before C++17)
    foo(std::make_unique<int>(42) /*gives basic exception safety*/, int{}); // OK
}