/**
 * @brief std::atomic semantics
 *
 */
#include "../../common.hpp"

#include <atomic>
#include <thread>

constexpr size_t kIter{1'000'000};

std::atomic<size_t> counter;

int main() {
    std::thread th1{[] {
        for (size_t i = 0; i < kIter; ++i) {
            ++counter;
        }
    }};

    std::thread th2{[] {
        for (size_t i = 0; i < kIter; ++i) {
            ++counter;
        }
    }};

    th1.join();
    th2.join();

    std::print("{}\n", counter.load());
}