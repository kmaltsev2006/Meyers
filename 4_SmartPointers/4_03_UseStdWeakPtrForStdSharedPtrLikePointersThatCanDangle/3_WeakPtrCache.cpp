/**
 * @brief std::weak_ptr lock
 *
 * Cache implementation
 *
 * BTW:
 * w_ptr <- sh_ptr <- u_ptr
 *  |         ^
 *  `---------'
 *
 */

#include "../../common.hpp"

#include <memory>
#include <unordered_map>
#include <utility>

class LifeTime {

    template <typename T>
    friend std::shared_ptr<T> fastLoad(const size_t id);

    using cache_t = std::unordered_map<size_t, std::weak_ptr<LifeTime>>;

  public:
    template <typename... Args>
    static auto create(Args&&... args) {
        return std::unique_ptr<LifeTime>{new LifeTime{std::forward<Args>(args)...}};
    }

    ~LifeTime() {
        PRINT_CALL();
        printId();
        _cache_ref.erase(_id);
    }

  private:
    size_t _id;
    cache_t& _cache_ref;

  private:
    explicit LifeTime(const size_t id, cache_t& cache) : _id{id}, _cache_ref{cache} {
        PRINT_CALL();
        printId();
    }

    void printId() const noexcept { std::cout << "_id: " << _id << std::endl; }
};

template <typename T>
std::shared_ptr<T> fastLoad(const size_t id) {
    static std::unordered_map<size_t, std::weak_ptr<T>> cache;

    auto sh_ptr = cache[id].lock();

    if (!sh_ptr) {
        sh_ptr = T::create(id, cache);
        cache[id] = sh_ptr;
    }

    return sh_ptr;
}

int main() {
    auto sh_ptr_obj0 = fastLoad<LifeTime>(0);

    auto sh_ptr_obj1 = fastLoad<LifeTime>(1);
    sh_ptr_obj1 = fastLoad<LifeTime>(1);

    {
        auto sh_ptr_obj2 = fastLoad<LifeTime>(2);
        sh_ptr_obj2 = fastLoad<LifeTime>(2);
    }

    auto sh_ptr_obj2 = fastLoad<LifeTime>(2);

    auto sh_ptr_obj3 = fastLoad<LifeTime>(3);
}