/**
 * @brief use std::move / std::forward only for LAST reference usage
 *
 * BTW: even if foo(const std::vector<T>&) was declared instead of
 * foo(std::vector<T>&), in the case of foo(std::forward<T>(t)) where t is an
 * rvalue, foo(std::vector<T>&&) will still be called by most match rule
 */
#include "../../common.hpp"

#include <utility>
#include <vector>

template <typename T>
void foo(std::vector<T>&) {
    PRINT_CALL();
}

template <typename T>
void foo(std::vector<T>&&) {
    PRINT_CALL();
}

template <typename T>
void modify(const std::vector<T>&) {
    PRINT_CALL();
}

int main() {
    static const auto lambda = []<typename T>(T&& t) {
        modify(t);
        foo(std::forward<T>(t));
    };

    std::vector<int> v{1, 2, 3};
    lambda(v);
    lambda(std::vector<int>{1, 2, 3});
}