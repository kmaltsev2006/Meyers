/**
 * @brief std::packaged_task
 *
 */
#include "../../common.hpp"

#include <future>
#include <thread>

constexpr size_t kIter{1'000'000};

int main() {
    const auto routine = [] {
        size_t ret{};
        for (size_t i = 0; i < kIter; ++i) {
            ++ret;
        }
        return ret;
    };

    std::packaged_task<size_t()> task{routine};
    auto f = task.get_future();

    std::jthread th{std::move(task)};
    std::cout << f.get() << std::endl;
}