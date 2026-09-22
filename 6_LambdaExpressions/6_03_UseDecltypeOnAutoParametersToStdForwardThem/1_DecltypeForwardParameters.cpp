/**
 * @brief Use decltype on auto&& parameters to std::forward them
 *
 */
#include "../../common.hpp"

#include <memory>

int main() {
    static const auto lambdaFactory = []<typename T>(auto&&... args) {
        return std::make_unique<T>(std::forward<decltype(args)>(args)...);
    };

    auto u_ptr = lambdaFactory.operator()<int>(42);
    std::cout << *u_ptr << std::endl;
}