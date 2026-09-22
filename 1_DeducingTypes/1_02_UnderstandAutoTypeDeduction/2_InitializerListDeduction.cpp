/**
 * @brief auto and template type deduction with std::initializer_list
 *
 */
#include <intializer_list>

#include "../../common.hpp"

void foo(auto) {}

template <typename T>
void bar(T) {}

auto baz() {
    return {1, 2, 3}; // error: returning initializer list
}

int main() {
    foo(42);
    foo({1, 2, 3}); // error: no matching function for call to
                    // foo(<brace-enclosed initializer list>)’

    bar(42);
    bar({1, 2, 3}); // error: no matching function for call to
                    // bar(<brace-enclosed initializer list>)’

    const auto lambda = [] { return {1, 2, 3}; }; // error: returning initializer list
}