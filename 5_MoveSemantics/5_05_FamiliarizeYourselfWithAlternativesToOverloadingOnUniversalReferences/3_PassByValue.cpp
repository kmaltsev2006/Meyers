/**
 * @brief Pass by value
 *
 */

#include "../../common.hpp"

#include <string>
#include <utility>

struct A {
    explicit A(std::string s) : _s{std::move(s)} { PRINT_CALL(); }

    explicit A(int) { PRINT_CALL(); }

    std::string _s;
};

int main() {
    using namespace std::string_literals;
    A a1{"qwe"s};
    A a2{int{}};
}