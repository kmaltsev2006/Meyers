/**
 * @brief std::enable_shared_from_this
 *
 */

#include "../../common.hpp"

#include <memory>
#include <unordered_map>
#include <utility>

class Widget : public std::enable_shared_from_this<Widget> {
  public:
    ~Widget() {
        PRINT_CALL();
        std::cout << "_id: " << _id << std::endl;
        _processed.erase(_next_id);
    }

    template <typename... Args>
    static std::shared_ptr<Widget> create(Args&&... args) {
        return std::shared_ptr<Widget>{new Widget{std::forward<Args>(args)...}};
    }

    void process() { _processed.insert(std::make_pair(_next_id, shared_from_this())); }

    static size_t processedCount() { return _processed.size(); }

  private:
    size_t _id;
    static size_t _next_id;

    static std::unordered_map<size_t, std::shared_ptr<Widget>> _processed;

  private:
    Widget() : _id{_next_id++} { PRINT_CALL(); }
};
size_t Widget::_next_id{0};
std::unordered_map<size_t, std::shared_ptr<Widget>> Widget::_processed{};

int main() {
    auto widget_sh_ptr1 = Widget::create();

    {
        auto widget_sh_ptr2 = Widget::create();
        auto widget_sh_ptr3 = Widget::create();

        widget_sh_ptr2->process();
        widget_sh_ptr3->process();

        std::cout << Widget::processedCount() << std::endl;
    }
    std::cout << Widget::processedCount() << std::endl;

    auto widget_sh_ptr4 = Widget::create();

    widget_sh_ptr1->process();

    std::cout << Widget::processedCount() << std::endl;
}