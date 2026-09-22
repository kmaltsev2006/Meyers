/**
 * @brief @brief Problems with deallocating memory when using std::make_shared
 *
 * When using std::make_shared (std::make_unique), the allocator uses only one
 * new call for the control block and object data. This leads to the fact that:
 * until the last weak_ptr is destroyed, memory for the object won't be
 * deallocated, even if the dtor is called.
 *
 * The complete opposite happens if using the std::shared_ptr (std::unique_ptr)
 * ctor: memory for the object will be deallocated immediately after the last
 * shared_ptr is destroyed. (But the control block, as before, only after the
 * last weak_ptr is destroyed).
 */

#include "../../common.hpp"

#include <memory>

struct BLOB {
    BLOB() : data{new char[size]{}} {}

    ~BLOB() {
        delete[] data;
        is_destroyed = true;
    }

    bool is_destroyed{false};
    const size_t size{1024};
    char* data;
};

int main() {

    auto sh_ptr_make = std::make_shared<BLOB>();
    {
        auto w_ptr = std::weak_ptr<BLOB>{sh_ptr_make};
        BLOB& blob_ref = *sh_ptr_make;
        std::cout << "is_destroyed: " << blob_ref.is_destroyed << std::endl;
        sh_ptr_make = nullptr;
        std::cout << "is_destroyed: " << blob_ref.is_destroyed
                  << std::endl; // UB, but it wont be found by sanitizer or valgrind
    }

    auto sh_ptr_raw = std::shared_ptr<BLOB>{new BLOB{}};
    {
        auto w_ptr = std::weak_ptr<BLOB>{sh_ptr_raw};
        BLOB& blob_ref = *sh_ptr_raw;
        std::cout << "is_destroyed: " << blob_ref.is_destroyed << std::endl;
        sh_ptr_raw = nullptr;
        std::cout << "is_destroyed: " << blob_ref.is_destroyed << std::endl; // UB
    }
}