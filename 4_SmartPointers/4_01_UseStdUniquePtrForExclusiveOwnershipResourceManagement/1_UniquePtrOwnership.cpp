/**
 * @brief Use std::unique_ptr for exclusiveownership resource management
 *
 */
#include <memory>
#include <type_traits>
#include <utility>

#include "../../common.hpp"

class Investment {
  public:
    virtual ~Investment() = 0;
};
Investment::~Investment() = default;

class Stock : public Investment {
  public:
    Stock(int) { PRINT_CALL(); }
    ~Stock() { PRINT_CALL(); }
};

class Bond : public Investment {
  public:
    Bond(double, double) { PRINT_CALL(); }
    ~Bond() { PRINT_CALL(); }
};

class RealEstate : public Investment {
  public:
    RealEstate(float) { PRINT_CALL(); }
    ~RealEstate() { PRINT_CALL(); }
};

template <typename I, typename... Ts>
auto makeInvestment(Ts&&... params) {
    static const auto delInvestment = [](Investment* p_investment) static {
        std::cout << "delInvestment called for object of type: " << typeid(*p_investment).name()
                  << std::endl;
        delete p_investment;
    };

    return std::unique_ptr<Investment, decltype(delInvestment)>{new I{std::forward<Ts>(params)...},
                                                                delInvestment};
}

int main() {
    std::cout << "sizeof(u_ptr): " << sizeof(std::unique_ptr<int>) << std::endl;

    makeInvestment<Stock>(0);
    makeInvestment<Bond>(0.0, 0.0);
    makeInvestment<RealEstate>(0.0f);
}