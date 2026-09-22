/**
 * @brief Polymorphic class dtor and copy/move assignment operators
 *
 * Not sure that code below is good from a scalability perspective
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
    explicit Poly(const bool do_init = false) {
        PRINT_CALL();
        if (do_init) {
            init();
        }
    }

    virtual ~Poly() = 0;

    Poly(const Poly& rhs) : _data_ptr{rhs._data_ptr ? new char{*rhs._data_ptr} : nullptr} {
        PRINT_CALL();
    }

    virtual Poly& operator=(const Poly& rhs) = 0;

    Poly(Poly&& rhs) : _data_ptr{std::exchange(rhs._data_ptr, nullptr)} { PRINT_CALL(); }

    virtual Poly& operator=(Poly&& rhs) = 0;

    void init() noexcept {
        delete _data_ptr;
        _data_ptr = new char{};
    }

    virtual const void* getDataPtr() const noexcept = 0;

  protected:
    char* _data_ptr{nullptr};
};
Poly::~Poly() {
    PRINT_CALL();
    delete _data_ptr;
}

class Derived : public Poly {
  public:
    explicit Derived(const bool do_init = false) : Poly{do_init} { PRINT_CALL(); }

    explicit Derived(const int val, const bool do_init = false) : Poly{do_init}, _val{val} {
        PRINT_CALL();
    }

    ~Derived() = default;

    Derived(const Derived& rhs) : Poly{rhs}, _val{rhs._val} { PRINT_CALL(); }

    Derived& operator=(const Poly& rhs) override {
        PRINT_CALL();
        if (this == &rhs)
            return *this;
        Derived tmp{dynamic_cast<const Derived&>(rhs)};
        _swap(tmp);
        return *this;
    }

    Derived& operator=(const Derived& rhs) {
        PRINT_CALL();
        if (this == &rhs)
            return *this;
        Derived tmp{rhs};
        _swap(tmp);
        return *this;
    }

    Derived(Derived&& rhs) : Poly{std::move(rhs)}, _val{rhs._val} { PRINT_CALL(); }

    Derived& operator=(Poly&& rhs) {
        PRINT_CALL();
        if (this == &rhs)
            return *this;
        Derived tmp{std::move(dynamic_cast<Derived&>(rhs))};
        _swap(tmp);
        return *this;
    }

    Derived& operator=(Derived&& rhs) {
        PRINT_CALL();
        if (this == &rhs)
            return *this;
        Derived tmp{std::move(rhs)};
        _swap(tmp);
        return *this;
    }

    const void* getDataPtr() const noexcept { return static_cast<void*>(_data_ptr); }

    auto getVal() const { return _val; }

  private:
    int _val{};

  private:
    void _swap(Derived& rhs) {
        std::swap(_data_ptr, rhs._data_ptr);
        std::swap(_val, rhs._val);
    }
};

int main() {
    Derived* a{new Derived{42, true}};
    Derived* b{new Derived{17, true}};

    Poly& a_r{*a};
    Poly& b_r{*b};

    std::cout << std::endl << "COPYING" << std::endl;

    a_r = b_r;

    std::cout << dynamic_cast<Derived&>(a_r).getVal() << std::endl;
    std::cout << dynamic_cast<Derived&>(b_r).getVal() << std::endl;

    *a = *b;

    std::cout << a->getDataPtr() << std::endl;
    std::cout << b->getDataPtr() << std::endl;

    std::cout << std::endl << "MOVING" << std::endl;
    a_r = std::move(b_r);

    std::cout << dynamic_cast<Derived&>(a_r).getVal() << std::endl;
    std::cout << dynamic_cast<Derived&>(b_r).getVal() << std::endl;

    std::cout << a->getDataPtr() << std::endl;
    std::cout << b->getDataPtr() << std::endl;

    delete a;
    delete b;
}