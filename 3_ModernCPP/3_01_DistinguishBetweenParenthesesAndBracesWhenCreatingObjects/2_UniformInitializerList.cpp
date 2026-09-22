/**
 * @brief Uniform initialization and std::initializer_list
 *
 */
#include <initializer_list>

#include "../../common.hpp"

class MyClass {
  public:
    MyClass() { PRINT_CALL(); }
    MyClass(int, double) { PRINT_CALL(); }
    MyClass(std::initializer_list<int>) { PRINT_CALL(); }
};

int main() {
    MyClass A{};

    MyClass B{int{}, double{}}; // error: narrowing conversion of ‘0.0’ from
                                // ‘double’ to ‘int’ [-Wnarrowing]

    MyClass C{int{}, int{}, int{}};

    MyClass D{{}};
}