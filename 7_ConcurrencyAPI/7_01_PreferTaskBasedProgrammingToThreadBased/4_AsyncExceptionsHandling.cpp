/**
 * @brief Exceptions handling with std::async
 *
 */
#include "../../common.hpp"

#include <future>

void willThrow() {
    PRINT_CALL();
    throw std::runtime_error{"runtime error"};
}

void wontThrow() noexcept { PRINT_CALL(); }

int main() {
    auto a1 = std::async(std::launch::async, willThrow);
    auto a2 = std::async(std::launch::async, wontThrow);

    try {
        a1.get();
    } catch (const std::exception& e) {
        std::print("Got: {} from a1\n", e.what());
    }

    try {
        a2.get();
    } catch (const std::exception& e) {
        std::print("Got: {} from a2\n", e.what());
    }
}