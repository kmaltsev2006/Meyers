/**
 * @brief std::future and std::shared_future dtor behaviour
 *
 * Consumer [future] <--- shared_state <--- [promise] Producer
 *
 * Consumer1 [shared_future] <--- shared_state <--- [promise] Producer
 * Consumer2 [shared_future] <----'     |
 * Consumer3 [shared_future] <----------'
 *
 * https://en.cppreference.com/cpp/thread/future/~future
 *
 * ~future();
 * Releases any shared state. This means:
 *
 * If the current object holds the last reference to its shared state, the shared state is
 * destroyed. The current object gives up its reference to its shared state.
 *
 * These actions will not block for the shared state to become ready, except that they may block if
 * all following conditions are satisfied: The shared state was created by a call to std::async. The
 * shared state is not yet ready. The current object was the last reference to the shared state.
 */
#include "../../common.hpp"

#include <chrono>
#include <future>
#include <thread>

int main() {
    using namespace std::chrono_literals;

    std::future<void> f = std::async(std::launch::async, [] { std::this_thread::sleep_for(2s); });

    std::shared_future<void> sh_f{f.share()};

    std::jthread jth1([sh_f] {
        std::this_thread::sleep_for(5s);
        sh_f.wait();
        std::print("Got sh_f from thread: {}\n", std::this_thread::get_id());
    }); // ~future will implictly call join on executor thread and destroy shared state

    std::jthread jth2([sh_f] {});

    std::jthread jth3([sh_f = std::move(sh_f)] {
        sh_f.wait();
        std::print("Got sh_f from thread: {}\n", std::this_thread::get_id());
    });

    std::print("main::sh_f is valid: {}\n", sh_f.valid());
}