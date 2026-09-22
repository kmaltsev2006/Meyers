/**
 * @brief Rule of 3
 *
 */
#include <format>
#include <utility>

#include "../../common.hpp"

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

    void init() noexcept {
        delete _data_ptr;
        _data_ptr = new char{};
    }

  private:
    char* _data_ptr{nullptr};

  private:
    void _swap(C& rhs) { std::swap(_data_ptr, rhs._data_ptr); }
};

int main() {
    C c0{true /*do_init*/};
    C c1{c0};
    c1 = c0;
}