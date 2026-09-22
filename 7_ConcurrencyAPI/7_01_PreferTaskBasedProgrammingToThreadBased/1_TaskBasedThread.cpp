/**
 * @brief Prefer task-based programming to thread-based (std::thread)
 *
 */
#include "../../common.hpp"

#include <mutex>
#include <thread>

std::mutex mutex;

// Guarded by mutex
auto asyncJob() {
    std::lock_guard lock{mutex};
    PRINT_CALL();
    return int{42};
}

int main() {
    std::thread t1{asyncJob}; // we can't get result of asyncJob
    std::thread t2{asyncJob}; // we can't get result of asyncJob

    t1.join();
    t2.join();
}