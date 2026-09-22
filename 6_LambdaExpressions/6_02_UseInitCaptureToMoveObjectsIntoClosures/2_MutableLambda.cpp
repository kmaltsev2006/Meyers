/**
 * @brief Mutable lambda
 *
 * operator() is const by default for lambdas
 * mutable key-word removes const qualifier
 *
class __lambda
  {
    public:
    inline constexpr void operator()() const {
        ...
    }

    // private:
    ...
  };
 */
#include "../../common.hpp"

int main() {
    // auto lambda = [x {42}]{x = 17}; // error: assignment of read-only variable ‘x’
    auto lambda = [x{42}]() mutable { x = 17; };
}