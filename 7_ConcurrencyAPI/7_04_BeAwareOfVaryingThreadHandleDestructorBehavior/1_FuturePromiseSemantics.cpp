/**
 * @brief std::future and std::promise semantics
 *
 */
#include "../../common.hpp"

#include <future>
#include <numeric>
#include <thread>
#include <vector>

template <typename T>
void sum(const std::vector<T>& v, std::promise<T>&& p) {
    p.set_value(std::accumulate(v.cbegin(), v.cend(), T{}));
}

void foo() {}

int main() {
    {
        std::promise<int32_t> p;
        std::future<int32_t> f{p.get_future()};

        auto as = std::async(std::launch::async, [p = std::move(p)]() mutable {
            sum(std::vector<int32_t>{1, 2, 3}, std::move(p));
        });
        std::cout << f.get() << std::endl;
    }

    {
        std::promise<int32_t> p;
        std::future<int32_t> f{p.get_future()};
        auto th = std::jthread(
            [p = std::move(p)]() mutable { sum(std::vector<int32_t>{1, 2, 3}, std::move(p)); });

        std::cout << f.get() << std::endl;
    }
}