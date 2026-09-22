/**
 * @brief Passing by value and slicing
 *
 */
#include "../../common.hpp"

class Base {
  public:
    Base() { PRINT_CALL(); }
    Base(const Base&) { PRINT_CALL(); }
    Base(Base&&) { PRINT_CALL(); }
    ~Base() { PRINT_CALL(); }
};

class Derived : public Base {
  public:
    Derived() { PRINT_CALL(); }
    Derived(const Derived&) { PRINT_CALL(); }
    Derived(Derived&&) { PRINT_CALL(); }
    ~Derived() { PRINT_CALL(); }
};

void foo(Base) {}

int main() {
    Derived d;
    std::print("CALL START\n");
    foo(d); // implicit cast Derived& -> Base&
    std::print("CALL END\n");
}