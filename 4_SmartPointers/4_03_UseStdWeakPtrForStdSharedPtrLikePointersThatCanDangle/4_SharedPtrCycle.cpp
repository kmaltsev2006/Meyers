/**
 * @brief Cycle pointers
 *
 */

#include "../../common.hpp"

#include <memory>

template <typename Derived>
class SharedCreatable {
  protected:
    static std::shared_ptr<Derived> create(auto&&... args) {
        return std::shared_ptr<Derived>{new Derived{std::forward<decltype(args)>(args)...}};
    }
};

class B;

class A : public SharedCreatable<A> {
    friend class SharedCreatable;

  public:
    ~A() { PRINT_CALL(); }

    static auto create(auto&&... args) {
        return SharedCreatable::create(std::forward<decltype(args)>(args)...);
    }

    void attachA(std::shared_ptr<B>& sh_ptr_b) { _sh_ptr_b = sh_ptr_b; }

  private:
    std::shared_ptr<B> _sh_ptr_b;

  private:
    A() { PRINT_CALL(); }
};

class B : private SharedCreatable<B> {
    friend class SharedCreatable;

  public:
    ~B() { PRINT_CALL(); }

    static auto create(auto&&... args) {
        return SharedCreatable::create(std::forward<decltype(args)>(args)...);
    }

    void attachB(std::shared_ptr<A>& sh_ptr_a) { _sh_ptr_a = sh_ptr_a; }

  private:
    // std::shared_ptr<A> _sh_ptr_a; // memory leak will occur
    std::weak_ptr<A> _sh_ptr_a; // solves memory leak

  private:
    B() { PRINT_CALL(); }
};

struct C {
  public:
    C() { PRINT_CALL(); }

    ~C() { PRINT_CALL(); }
};

int main() {
    auto sh_ptr_a = A::create();
    auto sh_ptr_b = B::create();

    sh_ptr_a->attachA(sh_ptr_b);
    sh_ptr_b->attachB(sh_ptr_a);
}