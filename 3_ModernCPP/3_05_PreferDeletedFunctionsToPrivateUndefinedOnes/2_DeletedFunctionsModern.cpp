/**
 * @brief Prefer deleted functions to private undefined ones (modern approach)
 *
 */
#include "../../common.hpp"

template <typename T, typename Y>
class B {
  public:
    void foo() {}
};

template <typename Y>
class B<int, Y> {
  public:
    void foo() = delete;
};

static void bar() = delete;

int main() {
    B<double, double> b1;
    b1.foo();
    B<int, double> b2;
    b2.foo(); // error: use of deleted function ‘void B<int, Y>::foo() [with Y =
              // double]’
    bar();    // error: use of deleted function ‘void bar()’
}