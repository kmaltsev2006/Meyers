/**
 * @brief Use constexpr whenever possible (ctor example)
 *
 */
#include "../../common.hpp"

class Vector2d {
    friend constexpr Vector2d operator+(const Vector2d& lhs, const Vector2d& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Vector2d& v2d);

  public:
    constexpr explicit Vector2d(const double x, const double y) : _x{x}, _y{y} {}

    ~Vector2d() = default;

  private:
    double _x;
    double _y;
};

constexpr Vector2d operator+(const Vector2d& lhs, const Vector2d& rhs) {
    return Vector2d{lhs._x + rhs._x, lhs._y + rhs._y};
}

std::ostream& operator<<(std::ostream& os, const Vector2d& v2d) {
    os << v2d._x << " " << v2d._y;
    return os;
}

int main() {
    auto new_vector = Vector2d{0, 1} + Vector2d{1, 0};

    std::cout << new_vector << std::endl;
}