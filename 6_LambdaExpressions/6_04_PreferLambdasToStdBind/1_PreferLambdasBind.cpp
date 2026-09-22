/**
 * @brief std::bind
 *
 * BTW: std::bind binds its params by COPY
 */

#include "../../common.hpp"

#include <functional>

void foo(int x, int y, const char* text) {
    std::cout << text << std::endl;
    std::cout << x << std::endl;
    std::cout << y << std::endl;

    x += 10;
    y += 10;
}

int main() {
    int x{0};
    int y{0};

    auto foo_bind = std::bind(foo, y, std::cref(x), std::placeholders::_1);

    foo_bind("Hi my name");
    x = 42;
    y = 42;
    foo_bind("is not");
    x = 17;
    y = 17;
    foo_bind("Jason Turner");
}