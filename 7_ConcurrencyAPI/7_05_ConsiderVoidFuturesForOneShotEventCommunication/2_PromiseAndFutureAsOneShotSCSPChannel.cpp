/**
 * @brief Use std::promise and std::future as communication one-shot channel
 *
 */
#include "../../common.hpp"

#include <chrono>
#include <future>

class OneShotDetector {
  public:
    void reactOnDetection(const std::function<void()>& reaction) {
        _p.get_future().wait();
        reaction();
    }

    void detect() noexcept { _p.set_value(); }

  private:
    std::promise<void> _p;
};

int main() {
    OneShotDetector detector;

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
