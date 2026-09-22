/**
 * @brief Prefer const_iterators to iterators
 *
 */
#include <algorithm>
#include <ranges>
#include <utility>
#include <vector>

#include "../../common.hpp"

int main() {
    std::vector<int> v{1, 2, 3};
    std::for_each(v.cbegin(), v.cend(), [](const /*const is redudant, but ok*/ auto& el) {
        std::cout << el << std::endl;
    });

    for (const auto& el : std::views::as_const(v)) {
        std::cout << el << std::endl;
    }
}