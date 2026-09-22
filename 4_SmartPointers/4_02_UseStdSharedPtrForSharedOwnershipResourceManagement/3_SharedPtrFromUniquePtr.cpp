/**
 * @brief Construction std::shared_ptr from std::unique_ptr
 *
 */

#include "../../common.hpp"

#include <memory>
#include <utility>

int main() {
    static const auto fabric = []<typename T, typename... Args>(Args&&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    };

    std::shared_ptr sh_ptr1 = fabric.operator()<int>(42);
}