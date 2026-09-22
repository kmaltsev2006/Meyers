/**
 * @brief Use std::promise and std::future as communication one-shot channel
 *
 */
#include "../../common.hpp"

#include <chrono>
#include <future>
#include <vector>

class OneShotDetectors {
  public:
    void reactOnDetection(const size_t n, const std::function<void()>& reaction) {
        std::vector<std::future<void>> detectors;
        std::shared_future<void> sh_f{_p.get_future().share()};
        for (size_t i = 0; i < n; ++i) {
            detectors.emplace_back(std::async(std::launch::async, [sh_f, reaction] {
                sh_f.wait();
                reaction();
            }));
        }
    }

    void detect() noexcept { _p.set_value(); }

  private:
    std::promise<void> _p;

  private:
    void reactOnDetection(const std::function<void()>& reaction) {
        _p.get_future().wait();
        reaction();
    }
};

int main() {
    OneShotDetectors detector;

    auto consumer = std::async(std::launch::async, [&detector] {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1s);
        detector.reactOnDetection(4, [] { std::print("Reacted\n"); });
    });

    auto producer = std::async(std::launch::async, [&detector] {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(2s);
        detector.detect();
    });
}
