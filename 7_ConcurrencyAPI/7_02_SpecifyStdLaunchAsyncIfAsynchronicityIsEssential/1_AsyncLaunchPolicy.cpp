/**
 * @brief Specify std::launch::async if asynchronicity is essential
 *
 */
#include "../../common.hpp"

#include <future>

constexpr size_t kIter{1'000'000'000};

void task() {
    std::cout << "Start" << std::endl;
    for (size_t i = 0; i < kIter; ++i) {
    }
    std::cout << "End" << std::endl;
}

void launch(std::launch policy) {
    auto res = std::async(policy, task);
    std::cout << "Callee continue 1" << std::endl;
    for (size_t i = 0; i < kIter; ++i) {
    }
    std::cout << "Callee continue 2" << std::endl;
    res.wait();
    std::cout << std::endl;
}

int main() {
    launch(std::launch::async);                         // launch asynchronously in different thread
    launch(std::launch::deferred);                      // launch synchronously after get/wait call
    launch(std::launch::async | std::launch::deferred); // launch as you want
}