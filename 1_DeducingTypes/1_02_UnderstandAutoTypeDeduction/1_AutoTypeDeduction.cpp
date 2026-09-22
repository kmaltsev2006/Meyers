/**
 * @brief auto type deduction
 *
 */

#include "../../common.hpp"

void foo(auto param) { printTypeCE<decltype(param)>(); }

void bar(auto& param) { printTypeCE<decltype(param)>(); }

void baz(auto&& param) { printTypeCE<decltype(param)>(); }

int main() {
    int x{};
    const int cx{x};
    const int& rx{x};

    // Same as template deduction

    foo(x);
    foo(cx);
    foo(rx);

    bar(x);
    bar(cx);
    bar(rx);

    baz(x);
    baz(int{});

    auto y{x};
    const auto cy{y};
    const auto& ry{y};
}