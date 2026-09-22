/**
 * @brief Avoid default capture modes
 *
 */
#include "../../common.hpp"

#include <functional>
#include <vector>

struct LifeTime {

    LifeTime() { PRINT_CALL(); }
    ~LifeTime() {
        std::cout << "Destoryed this: " << this << std::endl;
        PRINT_CALL();
    }

    void addHandler(std::vector<std::function<void()>>& handlers) {
        int local_var{42};
        handlers.emplace_back([=]() {
            std::cout << local_var << std::endl;
            std::cout << data << std::endl; // UB, bc data is not captured by copy, we get access
                                            // via this->data to it
            std::cout
                << "This: " << this
                << std::endl; // this is also captured, but ONLY pointer is copied, not whole object
        });
    }

  private:
    int data{17};
};

int main() {
    std::vector<std::function<void()>> handlers;
    {
        LifeTime lt;
        lt.addHandler(handlers);
    }

    for (const auto& h : handlers) {
        h();
    }
}