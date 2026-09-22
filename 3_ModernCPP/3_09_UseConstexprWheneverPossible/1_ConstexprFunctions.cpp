/**
 * @brief Use constexpr whenever possible
 *
 */
#include <random>

#include "../../common.hpp"

inline constexpr auto sum(const auto& a, const auto& b) { return a + b; }

class Random {
  public:
    template <std::integral T>
    static T gen(const T a, const T b) noexcept {
        std::uniform_int_distribution _dist{a, b};
        return _dist(_gen);
    }

  private:
    static std::random_device _rd;
    static std::mt19937 _gen;
};
std::random_device Random::_rd{};
std::mt19937 Random::_gen{_rd()};

int main() {
    constexpr auto sm1 = sum(1, 2);

    /*
    constexpr auto sm2 =
        sum(Random::gen<int>(0, 100),
            Random::gen<int>(0, 100)); // error: call to non-‘constexpr’
    function ‘static T
                                       // Random::gen(T, T) [with T = int]’
    */

    auto sm3 = sum(Random::gen<int>(0, 100), Random::gen<int>(0, 100));

    std::cout << sum(Random::gen<int>(0, 100), Random::gen<int>(0, 100)) << std::endl;
}