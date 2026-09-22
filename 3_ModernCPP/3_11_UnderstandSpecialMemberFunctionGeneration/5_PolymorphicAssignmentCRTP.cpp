/**
 * @brief Polymorphic class copy/move assigment operator via CRTP
 *
 * Not sure that code below is valid from a scalability perspective
 * If interface would be non‑trivial, undefined behavior may occur
 *
 * UPD: VERY BAD code example, copy/move ctors are NOT inherited and along side assignment operators
 * MUST NOT be virtual
 *
 * C.60: Make copy assignment non-virtual, take the parameter by const&, and return by non-const&
 * C.61: A copy operation should copy
 * C.62: Make copy assignment safe for self-assignment
 * C.63: Make move assignment non-virtual, take the parameter by &&, and return by non-const&
 * C.64: A move operation should move and leave its source in a valid state
 * C.65: Make move assignment safe for self-assignment
 * C.66: Make move operations noexcept
 * C.67: A base class should suppress copying, and provide a virtual clone instead, if “copying” is
 * desired
 */
#include <utility>

#include "../../common.hpp"

class Poly {
  public:
    virtual ~Poly() = 0;

    virtual Poly& operator=(const Poly&) = 0;
    virtual Poly& operator=(Poly&&) = 0;

    virtual void foo() const noexcept = 0;
};
Poly::~Poly() = default;

template <typename Base, typename Derived>
class VirtualAssignable : public Base {

    friend Derived;

  public:
    VirtualAssignable& operator=(const Base& rhs) override {
        PRINT_CALL();
        auto& thisDerived = static_cast<Derived&>(*this);
        thisDerived = dynamic_cast<const Derived&>(rhs);
        return thisDerived;
    }

    VirtualAssignable& operator=(Base&& rhs) override {
        PRINT_CALL();
        auto& thisDerived = static_cast<Derived&>(*this);
        thisDerived = std::move(dynamic_cast<Derived&>(rhs));
        return thisDerived;
    }

  private:
    VirtualAssignable() = delete;
};

class A : public VirtualAssignable<Poly, A> {
  public:
    explicit A(const int val) : _val{val} {}

    A(const A& rhs) : _val{rhs._val} {}

    A& operator=(const A& rhs) {
        PRINT_CALL();
        if (this == &rhs)
            return *this;
        A tmp{rhs};
        _swap(tmp);
        return *this;
    }

    A(A&& rhs)
        : _val{std::exchange(rhs._val, 0)} // exchange 0 used just for evidence
    {}

    A& operator=(A&& rhs) {
        PRINT_CALL();
        if (this == &rhs)
            return *this;
        A tmp{std::move(rhs)};
        _swap(tmp);
        return *this;
    }

    void foo() const noexcept {
        PRINT_CALL();
        std::cout << _val << std::endl;
    }

  private:
    int _val;

  private:
    void _swap(A& rhs) noexcept { std::swap(_val, rhs._val); }
};

int main() {
    A* x_ptr{new A{42}};
    A* y_ptr{new A{17}};

    Poly& x_r{*x_ptr};
    Poly& y_r{*y_ptr};

    x_r = y_r;
    x_r.foo();
    y_r.foo();

    x_r = std::move(y_r);
    x_r.foo();
    y_r.foo();

    delete x_ptr;
    delete y_ptr;
}