/**
 * @brief  Prefer std::make_unique and std::make_shared to direct use of new
 *
 */

#include "../../common.hpp"

#include <memory>
#include <utility>

namespace my {

template <typename T>
struct MakeUnique {
    typedef std::unique_ptr<T> obj_single;
};

template <typename T>
struct MakeUnique<T[]> {
    typedef std::unique_ptr<T[]> obj_array;
};

template <typename T, size_t size>
struct MakeUnique<T[size]> {
    struct invalid_type {};
};

template <typename T, typename... Args>
typename MakeUnique<T>::obj_single make_unique(Args&&... args) {
    return std::unique_ptr<T>{new T{std::forward<Args>(args)...}};
}

template <typename T>
typename MakeUnique<T>::obj_array make_unique(const size_t size) {
    return std::unique_ptr<T>{new std::remove_extent_t<T>[size] {}};
}

template <typename T, typename... Args>
typename MakeUnique<T>::invalid_type make_unique(Args&&...) = delete;

// Same for make_shared //

} // namespace my

constexpr size_t sz{10};

int main() {
    auto u_ptr = my::make_unique<int>(42);

    auto u_ptr_arr = my::make_unique<int[]>(sz);
    for (size_t i = 0; i < sz; ++i) {
        u_ptr_arr[i] = i;
    }

    // auto u_ptr_arr_other = my::make_unique<int[sz]>(); // error: use of
    // deleted function
}