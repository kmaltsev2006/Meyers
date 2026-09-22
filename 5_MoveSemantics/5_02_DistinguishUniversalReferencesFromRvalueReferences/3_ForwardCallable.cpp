/**
 * @brief std::forward and callable objects
 *
 */
#include "../../common.hpp"

#include <cassert>
#include <chrono>
#include <utility>

struct Callable {

    void operator()() & { PRINT_CALL(); }

    void operator()() && { PRINT_CALL(); }

    Callable() { PRINT_CALL(); }
    Callable(const Callable&) { PRINT_CALL(); }
    Callable(Callable&&) { PRINT_CALL(); }
};

void timeIt(auto&& func, auto&&... args) {
    using namespace std::chrono;
    const auto start = steady_clock::now();

    // Saves call qualifiers
    std::forward<decltype(func)>(func)(std::forward<decltype(args)>(args)...);

    // Doesn't save call qualifiers (lvalue version will be called)
    // func(std::forward<decltype(args)>(args)...);

    const auto end = steady_clock::now();
    std::cout << (end - start).count() << std::endl;
}

int main() {
    static const auto myFunc = [](const int64_t from, const int64_t to) {
        assert(from <= to);
        for (size_t i = from; i <= to; ++i) {
        }
    };

    timeIt(myFunc, 42, 4242);

    Callable collable;
    timeIt(collable);
    timeIt(Callable{});
}