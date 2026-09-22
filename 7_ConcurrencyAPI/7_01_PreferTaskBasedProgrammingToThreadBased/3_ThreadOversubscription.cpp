/**
 * @brief Oversubscription
 *
 */
#include "../../common.hpp"

#include <thread>
#include <vector>

void printThreadId(const size_t id) { std::cout << id << " "; }

constexpr size_t kIterCount = 1'000;

int main() {
    std::vector<std::thread> workers;
    for (size_t i = 0; i < 3 * std::thread::hardware_concurrency(); ++i) {
        workers.emplace_back([id = i] {
            for (size_t i = 0; i < kIterCount; ++i) {
                printThreadId(id);
                std::cout << std::endl;
            }
        });
    }

    for (auto& t : workers) {
        t.join();
    }
}