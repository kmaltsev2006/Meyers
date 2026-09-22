/**
 * @brief std::move
 *
 */

#include "../../common.hpp"

#include <type_traits>
#include <utility>

namespace my {

template <typename T>
struct remove_reference {
    using type = T;
};

template <typename T>
struct remove_reference<T&> {
    using type = T;
};

template <typename T>
struct remove_reference<T&&> {
    using type = T;
};

template <typename T>
using remove_reference_t = remove_reference<T>::type;

// Old school (C++11)
// template<typename T>
// [[nodiscard]]
// constexpr typename my::remove_reference<T>::type&&
// move(T&& obj) noexcept {
//     return static_cast<typename my::remove_reference<T>::type&&>(obj);
// }

// Modern (C++20)
[[nodiscard]]
constexpr decltype(auto) move(auto&& obj) noexcept {
    return static_cast<std::remove_reference_t<decltype(obj)>&&>(obj);
}

} // namespace my

int main() {
    int x{};
    int& y{x};
    int&& z{std::move(x)};

    printTypeCE<decltype(my::move(x))>(); // error: use of deleted function ‘void
                                          // printTypeCE() [with T = int&&]’
    printTypeCE<decltype(my::move(y))>(); // error: use of deleted function ‘void
                                          // printTypeCE() [with T = int&&]’
    printTypeCE<decltype(my::move(z))>(); // error: use of deleted function ‘void
                                          // printTypeCE() [with T = int&&]’
}