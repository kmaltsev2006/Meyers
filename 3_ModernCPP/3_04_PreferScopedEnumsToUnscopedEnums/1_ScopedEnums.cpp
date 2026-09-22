/**
 * @brief Prefer scoped enums to unscoped enums
 *
 */
#include <cstdint>
#include <format>
#include <tuple>
#include <type_traits>
#include <utility>

#include "../../common.hpp"

enum class Rgb : size_t { kRed, kGreen, kBlue };

template <typename Enum>
constexpr auto eId(Enum e) {
    return static_cast<std::underlying_type_t<Enum>>(e);
}

int main() {
    Rgb color{Rgb::kRed};

    std::tuple<uint8_t, uint8_t, uint8_t> pixel{251, 206, 177};

    std::cout << std::format("{:d}\n", std::get<eId(Rgb::kRed)>(pixel));
    std::cout << std::format("{:d}\n", std::get<eId(Rgb::kGreen)>(pixel));
    std::cout << std::format("{:d}\n", std::get<eId(Rgb::kBlue)>(pixel));

    // since C++23:
    std::cout << std::format("{:d}\n", std::get<std::to_underlying(Rgb::kRed)>(pixel));
    std::cout << std::format("{:d}\n", std::get<std::to_underlying(Rgb::kGreen)>(pixel));
    std::cout << std::format("{:d}\n", std::get<std::to_underlying(Rgb::kBlue)>(pixel));
}