/**
 * @brief std::shared_future semantics
 *
 */
#include "../../common.hpp"

#include <chrono>
#include <future>

int main() {
    using namespace std::chrono_literals;

    std::promise<void> ready;
    std::shared_future<void> sh_f{ready.get_future()};

    const auto firstRoutine = [sh_f = sh_f] mutable {
        std::print("First started\n");
        sh_f.wait();
        std::print("First finished\n");
    };

    const auto secondRoutine = [sh_f = sh_f] mutable {
        std::print("Second started\n");
        std::this_thread::sleep_for(5s);
        sh_f.wait();
        std::print("Second finished\n");
    };

    const auto thirdRoutine = [sh_f = sh_f] {
        std::print("Third started\n");
        std::print("Third finished\n");
    };

    [[maybe_unused]] auto a1 = std::async(std::launch::async, firstRoutine);
    [[maybe_unused]] auto a2 = std::async(std::launch::async, secondRoutine);
    [[maybe_unused]] auto a3 = std::async(std::launch::async, thirdRoutine);

    std::this_thread::sleep_for(2s);

    ready.set_value();
}