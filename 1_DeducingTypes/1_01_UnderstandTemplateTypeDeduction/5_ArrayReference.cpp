/**
 * @brief Reference on array
 *
 */
#include "../../common.hpp"

template <typename T, size_t N>
constexpr size_t getArrSize(T (&arr)[N]) {
    PRINT_CALL();
    std::cout << "N: " << N << std::endl;
    return N;
}

int main() {
    constexpr size_t kSz{42};
    int arr[kSz]{};
    getArrSize(arr);
    int* arr_ptr{arr};
    // getArrSize(arr_ptr); // note: mismatched types ‘T [N]’ and ‘int*’
    int new_arr[getArrSize(arr)]{};
}