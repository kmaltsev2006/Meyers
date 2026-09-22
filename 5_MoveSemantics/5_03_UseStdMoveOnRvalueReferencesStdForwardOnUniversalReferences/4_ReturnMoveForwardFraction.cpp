/**
 * @brief use std::move or std::forward when returning an rvalue or universal
 * reference which is a function parameter, provided that the function returns
 * by value
 *
 */
#include "../../common.hpp"

#include <cassert>
#include <numeric>
#include <utility>

class Fraction {
    using value_type = int64_t;

    friend std::ostream& operator<<(std::ostream& os, const Fraction& frac);

  public:
    explicit Fraction(const value_type _numerator, const value_type _denominator) {
        PRINT_CALL();
        assert(_denominator != 0);
        numerator = _numerator;
        denominator = _denominator;
    }

    ~Fraction() = default;

    Fraction(const Fraction& rhs) : numerator{rhs.numerator}, denominator{rhs.denominator} {
        PRINT_CALL();
    }

    Fraction& operator=(const Fraction& rhs) {
        PRINT_CALL();
        if (this == &rhs)
            return *this;
        Fraction copy{rhs};
        swap(copy);
        return *this;
    }

    Fraction(Fraction&& rhs)
        : numerator{std::exchange(rhs.numerator, value_type{})},
          denominator{std::exchange(rhs.denominator, value_type{})} {
        PRINT_CALL();
    }

    Fraction& operator=(Fraction&& rhs) {
        PRINT_CALL();
        if (this == &rhs)
            return *this;
        Fraction tmp{std::move(rhs)};
        swap(tmp);
        return *this;
    }

    void reduce() {
        auto d = std::gcd(numerator, denominator);
        numerator /= d;
        denominator /= d;
    }

  private:
    value_type numerator;
    value_type denominator;

  private:
    void swap(Fraction& rhs) {
        std::swap(numerator, rhs.numerator);
        std::swap(denominator, rhs.numerator);
    }
};

std::ostream& operator<<(std::ostream& os, const Fraction& frac) {
    os << frac.numerator << "/" << frac.denominator;
    return os;
}

template <typename T>
Fraction fraction(T&& frac) {
    frac.reduce();
    return std::forward<T>(frac); // same as ex3 idea
};

int main() {
    Fraction f{24, 8};
    [[maybe_unused]] const auto res1 = fraction(f);
    // std::cout << res1 << std::endl;

    [[maybe_unused]] const auto res2 = fraction(Fraction{32, 16});
    // std::cout << res2 << std::endl;
}