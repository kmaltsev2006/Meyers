/**
 * @brief RVO / NRVO
 *
 */
#include "../../common.hpp"

class A {
  public:
    A() { PRINT_CALL(); }
    ~A() { PRINT_CALL(); }
    A(const A&) { PRINT_CALL(); }
    A(A&&) { PRINT_CALL(); }
};

A rvo() {
    return A{}; // only ctor called
};

A nrvo() {
    A a;
    return a; // only ctor called
};

int main() {
    rvo();
    nrvo();
}