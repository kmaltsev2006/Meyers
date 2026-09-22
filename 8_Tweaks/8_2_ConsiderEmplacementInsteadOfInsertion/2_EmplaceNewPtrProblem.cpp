/**
 * @brief Memory leak due to exception in emplace
 *
 */
#include "../../common.hpp"

#include <memory>
#include <vector>

int main() {
    const auto deleter = []<typename T>(T* ptr) { delete ptr; };

    std::vector<std::unique_ptr<int, decltype(deleter)>> v;

    // INCORRECT
    // If exception will appear after creating int ptr, while creating node in container -> memory
    // leak
    // 1. Memory allocated for new int{42}
    // 2. Trying to allocate memory for new node in container <- if exception happens here -> memory
    // leak
    // 3. Constructing object on node memory
    v.emplace_back(new int{42}, deleter);

    // CORRECT
    v.push_back(std::unique_ptr<int, decltype(deleter)>{new int{42}, deleter});
}