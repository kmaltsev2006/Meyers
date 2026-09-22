/**
 * @brief Override rules
 *
 */
#include <vector>

#include "../../common.hpp"

class Base {
  public:
    virtual ~Base() = 0;

    virtual bool foo(const std::vector<int>&, size_t) const& noexcept = 0;
};
Base::~Base() = default;

class Derived : public Base {
  public:
    bool foo(const std::vector<int>& v, size_t desired_sz) const& noexcept override {
        PRINT_CALL();
        return v.size() >= desired_sz;
    }

    void bar() { PRINT_CALL(); }
};

int main() {
    Derived d;
    Base& b{d};

    b.foo(std::vector<int>{1, 2, 3}, 2);

    dynamic_cast<Derived&>(b).bar();
}