/**
 * @brief Use std::weak_ptr for std::shared_ptr pointers that can dangle
 *
 */

#include "../../common.hpp"

#include <memory>

int main() {
    std::shared_ptr sh_ptr{std::make_shared<int>(42)};

    std::weak_ptr w_ptr{sh_ptr};

    std::cout << "Expired: " << w_ptr.expired() << std::endl;

    sh_ptr = nullptr; // w_ptr becomes "dangling"

    std::cout << "Expired: " << w_ptr.expired() << std::endl;
}