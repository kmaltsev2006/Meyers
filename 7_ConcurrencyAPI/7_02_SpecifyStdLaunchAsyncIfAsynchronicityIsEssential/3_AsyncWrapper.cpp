/**
 * @brief std::async wrapper with std::launch::async policy
 *
 */
#include "../../common.hpp"

#include <future>
#include <utility>

template <typename F, typename... Args>
auto async(F&& f, Args&&... args) {
    return std::async(std::launch::async, std::forward<F>(f), std::forward<Args>(args)...);
}

int main() {
    auto fut = async([](const auto& a, const auto& b) { return a + b; }, 42, 17);
    std::cout << fut.get() << std::endl;
}