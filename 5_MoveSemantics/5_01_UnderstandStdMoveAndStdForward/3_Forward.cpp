/**
 * @brief std::forward
 *
 * Reference collapsing rule
 */

#include "../../common.hpp"

#include <type_traits>
#include <utility>

namespace my {

template <typename T>
[[nodiscard]]
constexpr T&& forward(std::remove_reference_t<T>& obj) noexcept {
    return static_cast<T&&>(obj);
}

template <typename T>
[[nodiscard]]
constexpr T&& forward(std::remove_reference_t<T>&& obj) noexcept {
    static_assert(!std::is_lvalue_reference_v<T>);
    return static_cast<T&&>(obj);
}

} // namespace my

void foo(int&) { PRINT_CALL(); }
void foo(int&&) { PRINT_CALL(); }

int main() {
    static const auto bar = []<typename T>(T&& param) {
        // printTypeCE<T> {};
        // printTypeCE<decltype(param)> {};
        foo(my::forward<decltype(param)>(param));
    };

    int x{};

    bar(x);     // T=int& | decltype(param)=int&
    bar(int{}); // T=int  | decltype(param)=int&&

    // foo(my::forward<int>(int{42}));
    // foo(my::forward<int&>(int{42})); // CE
}