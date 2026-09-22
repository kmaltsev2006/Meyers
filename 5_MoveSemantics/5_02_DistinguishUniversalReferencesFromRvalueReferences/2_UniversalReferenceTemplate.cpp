/**
 * @brief Distinguish universal references from rvalue references and template
 * classes
 *
 */
#include "../../common.hpp"

#include <array>
#include <cassert>

template <typename T, size_t N>
struct UselessContainer {

    void pushBack(const T& val) {
        PRINT_CALL();
        assert(_sz < N);
        _arr[_sz++] = val;
    }

    /**
     * @brief NOT the Universal Reference!!!
     *
     * bc T&& is known not when calling a method, but when creating a class (
     * i.e. UselessContainer<int, 16> --> void pushBack(int&& val) <-- rvalue
     * ref)
     */
    void pushBack(T&& val) {
        PRINT_CALL();
        assert(_sz < N);
        _arr[_sz++] = std::move(val);
    }

    /**
     * @brief Universal Reference
     *
     */
    template <typename Y>
    void foo(Y&&) {
        PRINT_CALL();
    }

    /**
     * @brief Universal Reference and you can call method only via rvalue object
     * :)
     *
     */
    template <typename Y>
    void baz(Y&&) && {
        PRINT_CALL();
    }

    std::array<T, N> _arr;
    size_t _sz{0};
};

int main() {
    static const auto fabric = [] { return UselessContainer<int, 64>{}; };

    UselessContainer<int, 16> uc;
    int x{};
    uc.pushBack(x);
    uc.pushBack(int{});

    uc.foo(x);
    uc.foo(int{});

    fabric().baz(x);
    fabric().baz(int{});

    // uc.baz(int{}); // error: passing ‘UselessContainer<int, 16>’ as ‘this’
    // argument discards qualifiers
}