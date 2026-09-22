/**
 * @brief Understand special member function generation
 *
 */
#include "../../common.hpp"

class A {
  public:
    A() { PRINT_CALL(); }
    A(const A&) { PRINT_CALL(); }
    A(A&&) { PRINT_CALL(); }
};

class B {
  public:
    B() { PRINT_CALL(); }
    ~B() = default;

    B(const B&) { PRINT_CALL(); }
    B& operator=(const B& rhs) {
        PRINT_CALL();
        if (this == &rhs)
            return *this;
        return *this;
    }

    /* B(B&&) implicitly deleted */
    /* B& operator=(B&&) implicitly deleted */
};

class C {
  public:
    C() { PRINT_CALL(); }
    C(const C&) { PRINT_CALL(); }
    /* C& operator=(C&&) implicitly generated */
};

class D {
  public:
    D() { PRINT_CALL(); }
    D& operator=(const D& rhs) {
        PRINT_CALL();
        if (this == &rhs)
            return *this;
        return *this;
    }
};

int main() {
    A a0;
    A a1{a0};             // copy ctor is invoked
    A a2{A{}};            // RVO (until C++17) | prvalue evaluation (since C++17)
    A a3{std::move(A{})}; // move ctor is invoked

    B b0;
    B b1{b0};             // copy ctor is invoked
    B b2{B{}};            // RVO (until C++17) | prvalue evaluation (since C++17)
    B b3{std::move(B{})}; // copy ctor is invoked

    C c0;
    C c1;
    c1 = c0; // copy assigment operator is invoked

    D d0;
    D d1;
    d1 = std::move(d0); // copy assigment operator is invoked
}