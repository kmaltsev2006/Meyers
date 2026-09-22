/**
 * @brief Declare overriding functions override
 *
 */
#include "../../common.hpp"

// BTW: final >= override >= virtual

class Grandpa {
  public:
    Grandpa() { PRINT_CALL(); }

    virtual ~Grandpa() = 0;

    virtual void foo(int) = 0;

    virtual void baz() final { PRINT_CALL(); }

  protected:
    int _field{42};
};
Grandpa::~Grandpa() { PRINT_CALL(); }

class Parent : public Grandpa {
  public:
    Parent() { PRINT_CALL(); }

    ~Parent() { PRINT_CALL(); }

    void foo(int) override { PRINT_CALL(); }

    // void foo(double) override { PRINT_CALL(); } // error: ‘void
    // Parent::foo(double)’ marked ‘override’, but does not override

    void bar() { std::cout << _field << std::endl; }
};

class Child : public Parent {
  public:
    Child() { PRINT_CALL(); }

    ~Child() { PRINT_CALL(); }

    void foo(int) override final { PRINT_CALL(); }

    // void baz() override { PRINT_CALL(); } // error: virtual function ‘virtual
    // void Child::baz()’ overriding final function

    void bar() { std::cout << -_field << std::endl; }
};

int main() {
    Grandpa* grandpa_ptr{new Child{}};

    grandpa_ptr->foo(int{});

    dynamic_cast<Parent*>(grandpa_ptr)->foo(int{}); // ???

    dynamic_cast<Parent*>(grandpa_ptr)->bar();
    dynamic_cast<Parent*>(grandpa_ptr)->baz();

    dynamic_cast<Child*>(grandpa_ptr)->bar();
    dynamic_cast<Child*>(grandpa_ptr)->baz();

    delete grandpa_ptr;
}