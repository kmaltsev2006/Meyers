/**
 * @brief Overloading with const T& and T&& aproach
 *
 * LVALUE
 * copies | moves
 *      1 |     0
 *
 * RVALUE
 * copies | moves
 *      0 |     1
 */
#include "../../common.hpp"

#include <vector>

class LifeTime {
  public:
    LifeTime() { PRINT_CALL(); }

    LifeTime(const LifeTime& rhs) { PRINT_CALL(); }

    LifeTime(LifeTime&& rhs) { PRINT_CALL(); }

    ~LifeTime() { PRINT_CALL(); }

    // LifeTime& operator=(const LifeTime& rhs) {
    //     PRINT_CALL();
    //     if (this == &rhs)
    //         return *this;
    //     LifeTime tmp {rhs};
    //     _swap(tmp);
    //     return *this;
    // }

    // LifeTime& operator=(LifeTime&& rhs) {
    //     PRINT_CALL();
    //     if (this == &rhs)
    //         return *this;
    //     LifeTime tmp {std::move(rhs)};
    //     _swap(tmp);
    //     return *this;
    // }

  private:
    // void _swap(LifeTime& rhs) {}
};

template <typename T>
class VectorWrapper {
  public:
    void pushBack(const T& obj) { _v.push_back(obj); }

    void pushBack(T&& obj) { _v.push_back(std::move(obj)); }

  private:
    std::vector<T> _v;
};

int main() {
    {
        std::print("LVALUE\n");
        VectorWrapper<LifeTime> v_wrapper;
        LifeTime life_time;
        v_wrapper.pushBack(life_time);
    }
    std::print("\n");

    {
        std::print("RVALUE\n");
        VectorWrapper<LifeTime> v_wrapper;
        v_wrapper.pushBack(LifeTime{});
    }
}