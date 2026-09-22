/**
 * @brief Rule of 5
 *
 */
#include "../../common.hpp"
#include <format>
#include <utility>

class C {
  public:
    explicit C(bool do_init = false) {
        if (do_init) {
            init();
        }
    }

    ~C() { delete _data_ptr; }

    C(const C& rhs) : _data_ptr{rhs._data_ptr ? new char{*rhs._data_ptr} : nullptr} {}

    C& operator=(const C& rhs) {
        if (this == &rhs)
            return *this;
        C tmp{rhs};
        _swap(tmp);
        return *this;
    }

    C(C&& rhs) : _data_ptr{std::exchange(rhs._data_ptr, nullptr)} {}

    C& operator=(C&& rhs) {
        if (this == &rhs)
            return *this;
        C tmp{std::move(rhs)};
        _swap(tmp);
        return *this;
    }

    void init() noexcept {
        delete _data_ptr;
        _data_ptr = new char{};
    }

  private:
    char* _data_ptr{nullptr};

  private:
    void _swap(C& rhs) noexcept { std::swap(_data_ptr, rhs._data_ptr); }
};

int main() {
    C c0{true /*do_init*/};
    C c1{c0};
    C c2{std::move(c0)};
    c1 = c2;
    c2 = std::move(c1);
}