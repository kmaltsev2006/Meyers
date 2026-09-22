/**
 * @brief std::move does not guarantee that object will be moved
 * (only that it will be casted to rvalue type)
 *
 */
#include "../../common.hpp"

struct A {
    A() = default;
    A(const A& rhs) { PRINT_CALL(); }
    A(A&& rhs) { PRINT_CALL(); }
};

struct B {
    B(const A a)           // copy ctor first call
        : _a(std::move(a)) // copy ctor second call
    {}

    A _a;
};

int main() {
    A a;
    B b{a};
}