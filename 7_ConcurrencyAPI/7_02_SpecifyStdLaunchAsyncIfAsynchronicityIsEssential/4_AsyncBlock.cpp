/**
 * @brief std::async blocks with when returned std::future is unused
 *
 */
#include "../../common.hpp"

#include <chrono>
#include <future>

int main() {
    std::print("Start at: {}\n", std::chrono::steady_clock::now().time_since_epoch());

    std::async(std::launch::async, [] {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(5s);
    });

    std::print("Continue at: {}\n", std::chrono::steady_clock::now().time_since_epoch());
}