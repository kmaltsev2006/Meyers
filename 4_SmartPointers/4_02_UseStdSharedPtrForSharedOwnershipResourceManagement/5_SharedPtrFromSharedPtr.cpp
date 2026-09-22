/**
 * @brief Construction std::shared_ptr from std::shared_ptr
 *
 */

#include "../../common.hpp"

#include <memory>
#include <utility>

struct LifeTime {
    ~LifeTime() { PRINT_CALL(); }
};

int main() {
    auto ptr = new LifeTime{};

    std::shared_ptr<LifeTime> sh_ptr1{ptr};
    std::shared_ptr<LifeTime> sh_ptr2{sh_ptr1}; // OK

    std::cout << "Use count: " << sh_ptr1.use_count() << std::endl;
    std::cout << "Use count: " << sh_ptr2.use_count() << std::endl;
}