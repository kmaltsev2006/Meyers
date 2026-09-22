/**
 * @brief std::async default launch policy and thread_local variables
 *
 */
#include "../../common.hpp"

#include <future>
#include <thread>

thread_local uint32_t answer_for_life{0};
constexpr size_t kIter{1'000'000};

void task() {
    std::cout << "Callable thread_id: " << std::this_thread::get_id() << std::endl;
    answer_for_life = 17;
}

int main() {
    answer_for_life = 42;

    std::cout << "Callee thread_id: " << std::this_thread::get_id() << std::endl;

    for (size_t i = 0; i < kIter; ++i) {
        // Scheduler has all rights to call task in callee thread via default policy
        // To imitate that we turn off std::launch::async
        for (size_t w = 0; w < std::thread::hardware_concurrency(); ++w) {
            std::async(/*std::launch::async | */ std::launch::deferred, task).get();
            if (answer_for_life != 42) {
                // Live this world ASAP
                std::terminate();
            }
        }
    }
}