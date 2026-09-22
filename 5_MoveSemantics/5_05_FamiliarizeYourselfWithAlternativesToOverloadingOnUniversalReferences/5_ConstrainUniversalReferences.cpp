/**
 * @brief Constraining templates that take universal references
 * (the presented method is depricated since C++20, because of concepts)
 *
 */

#include <type_traits>

#include "../../common.hpp"

class Person {
  public:
    template <typename T,
              typename = std::enable_if_t<!std::is_base_of_v<Person, std::decay_t<T>> &&
                                          !std::is_integral_v<std::remove_reference_t<T>>>>
    explicit Person(T&& n) : name{std::forward<T>(n)} {
        PRINT_CALL();
    }

    explicit Person(int) { PRINT_CALL(); }

  private:
    std::string name;
};

int main() {
    using namespace std::string_literals;

    Person("s"s);
    Person(int{});
}
