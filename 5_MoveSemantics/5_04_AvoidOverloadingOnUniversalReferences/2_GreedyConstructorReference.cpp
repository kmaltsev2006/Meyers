/**
 * @brief Same as previous, but case with ctor and copy ctor is shown
 *
 */

#include "../../common.hpp"

struct A {
    template <typename... T>
    explicit A(T&&...) {
        PRINT_CALL();
    }

    A(const A&) { PRINT_CALL(); }
};

int main() {
    A a1;
    auto a2{a1};
}