/**
 * @brief Make const member functions thread safe
 *
 */
#include <mutex>
#include <thread>
#include <vector>

#include "../../common.hpp"

class Polynomial {
    using roots_t = std::vector<double>;

  public:
    void change() {
        std::lock_guard lock{_mutex};

        // changing

        are_cached_roots_valid = false;
    }

    roots_t getRoots() const {
        std::lock_guard lock{_mutex};

        if (!are_cached_roots_valid) {
            _recalc();
        }

        return cached_roots;
    }

  private:
    mutable std::mutex _mutex;
    mutable bool are_cached_roots_valid{false};
    mutable roots_t cached_roots;

  private:
    void _recalc() const {
        cached_roots.clear();

        // recalculation

        are_cached_roots_valid = true;
    }
};

int main() {}