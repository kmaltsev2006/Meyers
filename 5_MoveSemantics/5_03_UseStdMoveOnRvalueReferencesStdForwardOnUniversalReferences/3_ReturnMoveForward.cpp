/**
 * @brief use std::move or std::forward when returning an rvalue or universal
 * reference which is a function parameter, provided that the function returns
 * by value
 *
 */
#include "../../common.hpp"

#include <algorithm>
#include <utility>

template <typename T>
concept ArithmeticType = requires { std::is_arithmetic_v<T>; };

template <ArithmeticType T, size_t Rows, size_t Cols>
class Matrix2d {
    static constexpr size_t rows = Rows;
    static constexpr size_t cols = Cols;

    template <bool is_const>
    struct BaseIterator {
        using difference_type = std::ptrdiff_t;

        // FIXME: must be contiguous_iterator_tag
        using category = std::forward_iterator_tag;

        using value_type = T;
        using ptr_type = std::conditional_t<is_const, const T*, T*>;
        using ref_type = std::conditional_t<is_const, const T&, T&>;

        ref_type operator*() const { return *_ptr; }
        ptr_type operator->() { return _ptr; }
        BaseIterator& operator++() {
            ++_ptr;
            return *this;
        }
        BaseIterator operator++(int) {
            BaseIterator tmp{*this};
            ++(*this);
            return tmp;
        }
        friend bool operator==(const BaseIterator& lhs, const BaseIterator& rhs) {
            return lhs._ptr == rhs._ptr;
        }
        friend bool operator!=(const BaseIterator& lhs, const BaseIterator& rhs) {
            return lhs._ptr != rhs._ptr;
        }

        explicit BaseIterator(ptr_type ptr) : _ptr{ptr} {}

      protected:
        ptr_type _ptr{nullptr};
    };

  public:
    using Iterator = BaseIterator<false /* is_const */>;
    using ConstIterator = BaseIterator<true /* is_const */>;

  public:
    Matrix2d() : _buf{new T[rows * cols]} { PRINT_CALL(); }

    explicit Matrix2d(const T& val) : Matrix2d() {
        PRINT_CALL();
        std::fill_n(begin(), rows * cols, val);
    }

    ~Matrix2d() {
        PRINT_CALL();
        delete[] _buf;
    }

    Matrix2d(const Matrix2d& rhs) {
        PRINT_CALL();
        if (rhs._buf) {
            _buf = new T[rows * cols];
            std::copy_n(rhs._buf, rows * cols, _buf);
        }
    }

    Matrix2d(Matrix2d&& rhs) : _buf{std::exchange(rhs._buf, nullptr)} { PRINT_CALL(); }

    Matrix2d& operator=(const Matrix2d& rhs) {
        PRINT_CALL();
        if (this == &rhs)
            return *this;
        Matrix2d copy{rhs};
        swap(copy);
        return *this;
    }

    Matrix2d& operator=(Matrix2d&& rhs) {
        PRINT_CALL();
        if (this == &rhs)
            return *this;
        Matrix2d tmp{std::move(rhs)};
        swap(tmp);
        return *this;
    }

    Matrix2d& operator+=(const Matrix2d& rhs) {
        PRINT_CALL();
        for (size_t i = 0; i < rows * cols; ++i) {
            _buf[i] += rhs._buf[i];
        }
        return *this;
    }

    size_t getRows() const noexcept { return rows; }
    size_t getCols() const noexcept { return cols; }

    Iterator begin() { return Iterator{_buf}; }
    Iterator end() { return Iterator{_buf + rows * cols}; }
    ConstIterator cbegin() const { return ConstIterator{_buf}; }
    ConstIterator cend() const { return ConstIterator{_buf + rows * cols}; }

  private:
    T* _buf{nullptr};

  private:
    void swap(Matrix2d& rhs) noexcept { std::swap(_buf, rhs._buf); }
};

template <typename T, size_t Cols, size_t Rows>
Matrix2d<T, Rows, Cols> operator+(Matrix2d<T, Rows, Cols>&& lhs,
                                  const Matrix2d<T, Rows, Cols>& rhs) {
    lhs += rhs;
    return std::move(lhs); // Meyers says that std::move needs to be used here to avoid
                           // copying, but since C++20, implicit move is invoked, bc
                           // return value is ravlue. Not to be confused with RVO here ('lhs'
                           // is a function parameter and not a local variable)
                           //
                           // In C++17 and before return without std::move here will cause
                           // copying!!!
}

int main() {
    Matrix2d<int16_t, 3, 2> a{42};
    Matrix2d<int16_t, 3, 2> b{7};

    std::cout << "---" << std::endl;
    const Matrix2d c = Matrix2d<int16_t, 3, 2>{42} + b;
    std::for_each(c.cbegin(), c.cend(), [cols = a.getCols()](const auto& el) {
        static size_t col{0};
        std::cout << el << " ";
        if (++col == cols) {
            col = 0;
            std::cout << std::endl;
        }
    });
}