/**
 * @brief Distinguish universal references from rvalue references
 *
 */
#include "../../common.hpp"

// Universal Reference
template <typename T>
void foo(T&&) {
    PRINT_CALL();
}

// Universal Reference via auto (since C++20)
void bar(auto&&) { PRINT_CALL(); }

// Rvalue reference
void baz(int&&) { PRINT_CALL(); }

int main() {
    int x{};

    foo(x);
    foo(42);

    bar(x);
    bar(42);

    baz(int{});
    // baz(x); // error: cannot bind rvalue reference of type int&&’ to lvalue
    // of type ‘int’
}