/**
 * @brief  Know how to view deduced types
 *
 */
#include "../../common.hpp"

namespace example {

template <typename T>
void printTypeCE() = delete;

template <typename T>
void printTypeNoCE(T) {
    char* demangled = abi::__cxa_demangle(typeid(std::string).name(), nullptr, nullptr, nullptr);
    std::cout << demangled << std::endl;
    std::free(demangled);
}

} // namespace example

int main() {
    std::cout << typeid(int{}).name() << std::endl; // use c++filt afterwards
    example::printTypeNoCE(std::string{});
}