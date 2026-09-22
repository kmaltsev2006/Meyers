/**
 * @brief Assume that move operations are not present, not cheap, and not used
 *
 * Very strange article...
 * Point: if there is no move ctor or move assigment operator,
 * copy ctor or copy assigment operator will be called
 * or if they are present, they might be as expensive as copy ctor or copy assigment operator
 *
 */
#include "../../common.hpp"

#include <array>

int main() {
    std::array<int, 4> a1{1, 2, 3, 4};
    std::cout << a1.size() << std::endl;
    auto a2 = std::move(a1); // O(n) complexity
    std::cout << a2.size() << std::endl;
}