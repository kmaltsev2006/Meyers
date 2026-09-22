/**
 * @brief std::weak_ptr lock
 *
 * Semantics
 */

#include "../../common.hpp"

#include <memory>
#include <optional>

template <typename T>
std::optional<T> getValue(const std::weak_ptr<T>& w_ptr) {
    if (auto sh_from_w_ptr = w_ptr.lock(); sh_from_w_ptr) {
        return std::make_optional(*sh_from_w_ptr);
    }
    return std::nullopt;
}

void printValue(const std::optional<auto>& opt) {
    if (opt.has_value()) {
        std::cout << opt.value() << std::endl;
    } else {
        std::cout << "null" << std::endl;
    }
}

int main() {
    std::shared_ptr sh_ptr{std::make_shared<int>(42)};

    std::weak_ptr w_ptr{sh_ptr};

    printValue(getValue(w_ptr));

    sh_ptr = nullptr; // w_ptr becomes "dangling"

    printValue(getValue(w_ptr));
}