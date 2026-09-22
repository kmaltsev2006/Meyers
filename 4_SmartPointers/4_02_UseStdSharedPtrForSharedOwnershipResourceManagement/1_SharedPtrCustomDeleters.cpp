/**
 * @brief Storing std::shared_ptr with different deleters in container
 *
 */
#include "../../common.hpp"

#include <memory>
#include <vector>

int main() {
    static const auto del1 = []<typename T>(T* p_obj) {
        std::cout << "del1" << std::endl;
        delete p_obj;
    };

    static const auto del2 = []<typename T>(T* p_obj) {
        std::cout << "del2" << std::endl;
        delete p_obj;
    };

    std::vector<std::shared_ptr<int>> v = {{new int{}, del1}, {new int{}, del2}};
}
