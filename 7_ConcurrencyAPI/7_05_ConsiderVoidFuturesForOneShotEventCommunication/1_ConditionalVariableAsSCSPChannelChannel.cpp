/**
 * @brief
 *
 */
#include "../../common.hpp"

#include <chrono>
#include <condition_variable>
#include <future>

class Detector {
  public:
    void reactOnDetection(const std::function<void()>& reaction) {
        std::unique_lock lock{_mutex};
        _cv.wait(lock, [this] { return _detected; });
        _detected = false; // remove detection flag
        reaction();
    }

    void detect() noexcept {
        std::lock_guard lock{_mutex};
        _detected = true;
        _cv.notify_one();
    }

  private:
    std::mutex _mutex;
    std::condition_variable _cv;
    bool _detected{false};
};

int main() {
    Detector detector;

    auto consumer = std::async(std::launch::async, [&detector] {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(2s);
        detector.reactOnDetection([] { std::print("Reacted\n"); });
    });

    auto producer = std::async(std::launch::async, [&detector] {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1s);
        detector.detect();
    });
}