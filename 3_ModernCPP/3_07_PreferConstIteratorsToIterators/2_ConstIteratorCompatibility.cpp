/**
 * @brief Const iterator backwards compatibility work around
 *
 * Useless...
 */
#include <vector>

#include "../../common.hpp"

namespace my {

template <typename T>
auto cbegin(const T& cont) {
    return std::begin(cont);
}

} // namespace my

int main() {
    std::vector<int> v{1, 2, 3};

    auto cbegin_it = my::cbegin(v);
    *cbegin_it = 42; // error: assignment of read-only location
                     // ‘cbegin_it.__gnu_cxx::__normal_iterator<const int*,
                     // std::vector<int> >::operator*()’
}