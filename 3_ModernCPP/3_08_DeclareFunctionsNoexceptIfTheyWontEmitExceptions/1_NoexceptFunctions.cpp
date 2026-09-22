/**
 * @brief Declare functions noexcept if they won’t emit exceptions
 *
 */
#include <stdexcept>

#include "../../common.hpp"

constexpr bool kIsBazNoexcept{false};

void foo() noexcept { throw std::runtime_error{"Runtime error"}; }

void bar() noexcept(kIsBazNoexcept) { throw std::runtime_error("Runtime error"); }

int main() {
    try {
        foo();
        bar();
    } catch (const std::exception& e) { // error from foo won't be caught, but one from bar will
        std::cout << e.what() << std::endl;
    }
}