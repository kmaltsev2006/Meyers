/**
 * @brief ThreadRAII
 *
 */
#include "../../common.hpp"

#include <thread>

enum class ThreadRAIIDtorPolicy { kJoin, kDetach };

template <ThreadRAIIDtorPolicy dtor_policy = ThreadRAIIDtorPolicy::kJoin>
class ThreadRAII {
  public:
    ThreadRAII(std::thread&& t) : meta_data_1{}, meta_data_2{}, meta_data_3{}, _t{std::move(t)} {}

    ThreadRAII(ThreadRAII&&) = default;
    ThreadRAII& operator=(ThreadRAII&&) = default;

    ~ThreadRAII() {
        if constexpr (dtor_policy == ThreadRAIIDtorPolicy::kJoin) {
            join();
        } else if constexpr (dtor_policy == ThreadRAIIDtorPolicy::kDetach) {
            detach();
        } else {
            static_assert(false, "Unknown ThreadRAIIDtorPolicy");
        }
    }

  private:
    char meta_data_1;
    char meta_data_2;
    char meta_data_3;
    std::thread _t; // declare std::thread objects LAST, it otherwise might use uninitialized fields
                    // after immediately starting to execute

  private:
    void join() {
        if (_t.joinable()) {
            _t.join();
        }
    }

    void detach() {
        if (_t.joinable()) {
            _t.detach();
        }
    }
};

int main() {
    ThreadRAII<ThreadRAIIDtorPolicy::kUnknown> th{std::thread{[] {}}};

    std::thread t;

    std::vector<int> a(-1);
}