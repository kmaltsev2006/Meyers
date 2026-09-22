/**
 * @brief Make std::threads unjoinable on all paths
 *
 * BTW: be careful with detaching threads, because they might use references on local variables,
 * wich become dangling after current scope ends
 */
#include "../../common.hpp"

#include <functional>
#include <random>
#include <thread>

class RandomBool {
  public:
    bool operator()() { return static_cast<bool>(_dist(_rng)); }

  private:
    static std::random_device _rd;
    static std::mt19937 _rng;
    static std::uniform_int_distribution<> _dist;
};
std::random_device RandomBool::_rd{};
std::mt19937 RandomBool::_rng{_rd()};
std::uniform_int_distribution<> RandomBool::_dist{0, 1};

bool executeInParallel(const std::function<void()>& task) {
    const size_t iter{1'000};

    // task and iter becomes dangling after executeInParallel finishes if thread is detached
    const auto job = [&task, &iter] {
        for (size_t i = 0; i < kIter; ++i) {
            task();
        }
        std::cout << "Job finished" << std::endl;
    };

    std::thread t{job};

    auto nh = t.native_handle();
    // ...

    if (RandomBool{}()) {
        // Good case scenario
        t.join();
        std::cout << "Joined" << std::endl;
        return true;
    }

    // Bad case scenario
    t.detach(); // UB invoked
    std::cout << "Detached" << std::endl;
    return false;
}

int main() {
    std::cout << std::boolalpha << executeInParallel([x = static_cast<size_t>(0)] mutable { ++x; })
              << std::noboolalpha << std::endl;
}