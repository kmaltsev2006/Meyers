/**
 * @brief Reference collapsing
 *
 * 1 level approach:
 * & & -> &
 * & && -> &
 * && & -> &
 * && && -> &&
 *
 * 2 level approach:
 * Coding T type in templates:
 * if LVALUE passed: deduce T&
 * if RVALUE passed: deduce T
 *
 * Also can be anderstood like that:
 * template takes off all references, then adds one if LVALUE passed
 *
 * Then reference collapsing rules are applied:
 * T& && -> T&
 * T  && -> T&&
 *
 * 2.1 level approach (how universal references work):
 * & && -> &
 * - && -> &&
 *
 * 3. Lets take a look at example foo(rrx):
 * foo(auto&&);
 * int&& rrx {0};
 * foo(rrx); // What happens:
 *
 * template removes && and adds back & (bc rrx is LVALUE)
 * foo(int& &&) collapses in foo(int&)
 *
 * 3.1 Similarly foo(int{}):
 * template removes nothing and adds back nothing (bc int{} is RVALUE)
 * foo(int &&) collapses in foo(int&&)
 *
 * BTW: use -v flag for compilation
 */
#include "../../common.hpp"

void foo(auto&& t) { printTypeCE<decltype(t)>(); }

void bar(int&& t) { printTypeCE<decltype(t)>(); }

int main() {
    int x{};
    int& rx{x};
    int&& rrx{0};

    foo(x); // error: use of deleted function ‘void printTypeCE() [with T = int&]’

    foo(rx); // error: use of deleted function ‘void printTypeCE() [with T = int&]’

    // rrx is LVALUE, and its type is int&& (RVALUE reference) so in foo(auto&&) collapsed type is
    // int&
    foo(rrx); // error: use of deleted function ‘void printTypeCE() [with T = int&]’

    // int{} is RVALUE, and its type is int so in foo(auto&&) collapsed type is int
    foo(int{}); // error: use of deleted function ‘void printTypeCE() [with T = int&&]’

    bar(rrx); // error: cannot bind rvalue reference of type ‘int&&’ to lvalue of type ‘int’
    bar(int{});
}