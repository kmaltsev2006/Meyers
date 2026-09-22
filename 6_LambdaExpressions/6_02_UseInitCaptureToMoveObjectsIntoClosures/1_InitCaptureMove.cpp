/**
 * @brief Use init (generalized) capture to move objects into closures
 *
 */
#include "../../common.hpp"

#include <memory>
#include <utility>

class LifeTime {
  public:
    LifeTime() { PRINT_CALL(); }
    ~LifeTime() { PRINT_CALL(); }
    LifeTime(const LifeTime&) { PRINT_CALL(); }
    LifeTime(LifeTime&&) { PRINT_CALL(); }

    void modify() { PRINT_CALL(); }
};

template <typename T>
auto factoryPreModificationHandler(auto&&... args) {
    std::unique_ptr u_ptr_obj{std::make_unique<T>(std::forward<decltype(args)>(args)...)};

    u_ptr_obj->modify();
    return [u_ptr_obj = std::move(u_ptr_obj)] {
        std::cout << "Captured via move: " << u_ptr_obj.get() << std::endl;
    };
}

template <typename T>
auto factoryPostModificationHandler(auto&&... args) {

    return [u_ptr_obj = std::make_unique<T>(std::forward<decltype(args)>(args)...)] {
        std::cout << "Captured via move: " << u_ptr_obj.get() << std::endl;
        u_ptr_obj->modify();
    };
}

int main() {
    {
        auto handler = factoryPreModificationHandler<LifeTime>();
        handler();
        handler();
    }

    std::cout << std::endl;

    {
        auto handler = factoryPostModificationHandler<LifeTime>();
        handler();
        handler();
    }
}