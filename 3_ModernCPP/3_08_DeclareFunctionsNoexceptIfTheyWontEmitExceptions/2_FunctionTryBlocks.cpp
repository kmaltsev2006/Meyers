/**
 * @brief Functions and ctors try blocks
 *
 */
#include <format>
#include <stdexcept>

#include "../../common.hpp"

class GoodBoy {};

class BadBoy {
  public:
    BadBoy() { throw std::logic_error{"Logic error"}; }
};

class A {
  public:
    A() try : _good_boy_ptr{new GoodBoy{}
}, _bad_boy_ptr{new BadBoy{}} {
    PRINT_CALL();
}
catch (const std::exception& e) {
    std::cout << std::format("Got exception ({}) wich will be thrown further", e.what())
              << std::endl;
}

~A() noexcept /* implicitly */ {
    PRINT_CALL();
    delete _good_boy_ptr;
    delete _bad_boy_ptr;
}

private:
GoodBoy* _good_boy_ptr{nullptr};
BadBoy* _bad_boy_ptr{nullptr};
}
;

void foo() try { throw std::runtime_error{"Runtime error"}; } catch (const std::exception& e) {
    std::cout << std::format("{}", e.what()) << std::endl;
}

int main() {

    try {
        A a;
    } catch (const std::exception& e) {
        std::cout << std::format("Got exception ({}) from A ctor", e.what()) << std::endl;
    }

    foo();
}