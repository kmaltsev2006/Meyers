/**
 * @brief Prefer task-based programming to thread-based (std::async)
 *
 */
#include "../../common.hpp"

#include <future>
#include <mutex>

std::mutex mutex;

// Guarded by mutex
auto asyncJob() {
    std::lock_guard lock{mutex};
    PRINT_CALL();
    return int{42};
}

int main() {
    using result_t = decltype(asyncJob());

    std::future<result_t> result1 = std::async(asyncJob);
    std::future<result_t> result2 = std::async(asyncJob);

    std::cout << "Get first result" << " ";
    std::cout << result1.get() << std::endl;
    std::cout << "Get second result" << " ";
    std::cout << result2.get() << std::endl;
}