/**
 * @brief Prefer deleted functions to private undefined ones (C++98 approach)
 *
 */
#include "../../common.hpp"

class A {
  public:
    static void foo(int) {}

  private:
    static void foo(double);
};

int main() {
    A::foo(int{});
    A::foo(double{}); // error: ‘static void A::foo(double)’ is private within
                      // this context
}