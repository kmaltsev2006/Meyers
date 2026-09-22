/**
 * @brief push vs emplace
 *
 */
#include "../../common.hpp"

#include <vector>

class LifeTime {
  public:
    explicit LifeTime([[maybe_unused]] size_t n) { PRINT_CALL(); }
    LifeTime(const LifeTime&) { PRINT_CALL(); }
    LifeTime(LifeTime&&) { PRINT_CALL(); }
    ~LifeTime() { PRINT_CALL(); }
};

int main() {
    {
        std::print("push_back\n");
        std::vector<LifeTime> v;
        v.push_back(LifeTime{42});
    }

    {
        std::print("emplace_back\n");
        std::vector<LifeTime> v;
        v.emplace_back(42);
    }
}