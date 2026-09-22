/**
 * @brief Construction std::shared_ptr from lvalue raw ptr
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
    std::shared_ptr<LifeTime> sh_ptr2{ptr}; // UB

    // 2 control blocks will be created for one object
    // -> memory will be freed 2 times for each one -> double free

    std::cout << "Use count: " << sh_ptr1.use_count() << std::endl; // 1
    std::cout << "Use count: " << sh_ptr2.use_count() << std::endl; // 1
}