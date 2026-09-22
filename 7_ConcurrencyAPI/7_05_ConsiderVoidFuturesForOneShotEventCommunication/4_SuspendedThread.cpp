/**
 * @brief
 *
 */
#include "../../common.hpp"

#include <future>
#include <thread>

class SuspendedJThread {
  public:
    template <typename Func, typename... Args>
    SuspendedJThread(Func&& action, Args&&... args)
        : _th{[this, action = std::forward<Func>(action),
               ... args = std::forward<Args>(args)] mutable {
              wrapperRoutine(std::forward<Func>(action), std::forward<Args>(args)...);
          }} {}

    void start() { _start.set_value(); }

  private:
    std::promise<void> _start;
    std::jthread _th; // declare std::thread objects LAST, it otherwise might use uninitialized
                      // fields after immediately starting to execute

  private:
    template <typename Func, typename... Args>
    void wrapperRoutine(Func&& action, Args&&... args) {
        _start.get_future().wait();
        std::forward<Func>(action)(std::forward<Args>(args)...);
    }
};

int main() {
    uint64_t a = 0xAA;
    uint64_t b = 0xBB;

    SuspendedJThread jth{[](uint64_t a, uint64_t b) { std::cout << a + b << std::endl; }, a,
                         static_cast<uint64_t>(0xBB)};

    jth.start();
}