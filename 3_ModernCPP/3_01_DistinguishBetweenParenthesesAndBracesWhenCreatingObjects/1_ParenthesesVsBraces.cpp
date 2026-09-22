/**
 * @brief Distinguish between () and {} when creating objects
 *
 */
#include "../../common.hpp"

class C {
  public:
    C() { PRINT_CALL(); }

    ~C() { PRINT_CALL(); }

    C(const C& rhs) : field{rhs.field} { PRINT_CALL(); }

    C& operator=(const C& rhs) {
        PRINT_CALL();
        if (this == &rhs) {
            return *this;
        }
        C tmp{rhs};
        swap(tmp);
        return *this;
    }

    C(C&& rhs) : field{std::move(rhs.field)} { PRINT_CALL(); }

    C& operator=(C&& rhs) {
        PRINT_CALL();
        if (this == &rhs) {
            return *this;
        }
        C tmp{std::move(rhs)};
        swap(tmp);
        return *this;
    }

  private:
    int field{};

  private:
    void swap(C& rhs) { std::swap(field, rhs.field); }
};

struct Data {
    int a{1};
    int b{2};
    int c{3};
};

std::ostream& operator<<(std::ostream& os, const Data& d) {
    os << d.a << " " << d.b << " " << d.c;
    return os;
}

int main() {
    // Uniform initialization
    int x(42);
    int y{42};
    int z = 42;
    int w = {42};

    C c1{};
    C c2{};
    C c3{c1};
    C c4 = c1;   // C::C(const C&)
    C c5 = {c1}; // C::C(const C&)

    C c6{std::move(C{})};    // C::C(C&&)
    C c7{std::move(C{})};    // C::C(C&&)
    C c8 = {std::move(C{})}; // C::C(C&&)

    // Designated initialization
    Data d1{.a = 42, .c = 17};
    std::cout << d1 << std::endl;

    // Aggregate initialization
    Data d2{42, 15};
    std::cout << d2 << std::endl;
}