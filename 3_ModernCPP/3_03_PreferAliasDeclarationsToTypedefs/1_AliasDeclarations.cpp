/**
 * @brief Prefer alias declarations to typedefs
 *
 */
#include <vector>

#include "../../common.hpp"

// Pointer to function:
typedef bool (*cmp1)(const int, const int);
using cmp2 = bool (*)(const int, const int);

// Dependent type case:
template <typename T>
struct A1 {
    typedef std::vector<T> type;
};

template <typename T>
struct A2 {
    typename A1<T>::type v;
};

template <typename T>
struct B1 {
    using type = std::vector<T>;
};

template <typename T>
struct B2 {
    typename B1<T>::type v;
};

namespace C1 {
template <typename T>
using type = std::vector<T>;
} // namespace C1

template <typename T>
struct C2 {
    C1::type<T> v;
};

int main() {
    A2<int> a2;
    std::cout << a2.v.size() << std::endl;

    B2<int> b2;
    std::cout << b2.v.size() << std::endl;

    C2<int> c2;
    std::cout << c2.v.size() << std::endl;
}