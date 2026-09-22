/**
 * @brief  Use std::move on rvalue references, std::forward on universal
 * references.
 *
 */
#include "../../common.hpp"

#include <cstring>
#include <utility>

struct DataWrapper {
    friend int main();
    using value_type = int;

    DataWrapper() = default;

    void tryAllocate() {
        if (!data) {
            data = new value_type[sz];
        }
    }

    void fill() {
        tryAllocate();
        for (size_t i = 0; i < sz; ++i) {
            data[i] = i;
        }
    }

    DataWrapper(const DataWrapper& rhs) {
        PRINT_CALL();
        if (rhs.data) {
            tryAllocate();
            std::memcpy(data, rhs.data, sizeof(value_type) * sz);
        }
    }

    DataWrapper& operator=(const DataWrapper& rhs) {
        PRINT_CALL();

        if (this == &rhs)
            return *this;

        if (rhs.data) {
            tryAllocate();
            std::memcpy(data, rhs.data, sizeof(value_type) * sz);
        } else {
            delete[] data;
            data = nullptr;
        }

        return *this;
    }

    DataWrapper(DataWrapper&& rhs) : data{std::exchange(rhs.data, nullptr)} { PRINT_CALL(); }

    DataWrapper& operator=(DataWrapper&& rhs) {
        PRINT_CALL();

        if (this == &rhs)
            return *this;
        delete[] data;
        data = std::exchange(rhs.data, nullptr);
        return *this;
    }

    ~DataWrapper() { delete[] data; }

  private:
    value_type* data{nullptr};
    static constexpr size_t sz{1024};
};

struct A {
    A() = default;

    template <typename T>
    A(T&& rhs)
        : dw{std::move(rhs)} // UB !!!
    {}

    DataWrapper dw;
};

struct B {
    B() = default;

    template <typename T>
    B(T&& rhs)
        : dw{std::forward<T>(rhs)} // OK
    {}

    DataWrapper dw;
};

int main() {
    A a_src;
    a_src.dw.fill();
    A a_dest{a_src.dw};                                // UB
    printf("%p\n", static_cast<void*>(a_src.dw.data)); // (nil)
    std::cout << a_src.dw.data[16] << std::endl;       // Segmentation fault (UB invoked)

    B b_src;
    b_src.dw.fill();
    B b_dest{b_src.dw}; // OK
    printf("%p\n", static_cast<void*>(b_src.dw.data));
    std::cout << b_src.dw.data[16] << std::endl;
}