/**
 * @brief Use the ETI (explicitly typed initializer) idiom when auto deduces
 * undesired types
 *
 */
#include <vector>

#include "../../common.hpp"

int main() {
    std::vector<bool> v{true, false, true};
    auto first_proxy = v[0];
    printTypeNoCE(first_proxy);

    auto first = static_cast<bool>(v[0]); // ETI
    printTypeNoCE(first);
}