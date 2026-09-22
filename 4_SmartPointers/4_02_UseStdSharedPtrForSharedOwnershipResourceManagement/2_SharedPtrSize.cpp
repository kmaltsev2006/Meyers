/**
 * @brief sizeof std::shared_ptr
 *
 */

#include "../../common.hpp"

#include <memory>

int main() { std::cout << sizeof(std::shared_ptr<int>) << std::endl; }