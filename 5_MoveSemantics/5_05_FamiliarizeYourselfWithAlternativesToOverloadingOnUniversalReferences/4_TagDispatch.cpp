/**
 * @brief Use Tag dispatch
 *
 */

#include "../../common.hpp"

#include <type_traits>
#include <utility>

template <typename T>
void fooImpl(T&& s, [[maybe_unused]] std::false_type /* tag */) {
    PRINT_CALL();
}

void fooImpl(int, [[maybe_unused]] std::true_type /* tag */) { PRINT_CALL(); }

template <typename T>
void foo(T&& v) {
    fooImpl(std::forward<T>(v), std::is_integral<std::remove_reference_t<T>>{});
}

int main() {
    using namespace std::string_literals;
    foo("s"s);
    foo(int{});
}
