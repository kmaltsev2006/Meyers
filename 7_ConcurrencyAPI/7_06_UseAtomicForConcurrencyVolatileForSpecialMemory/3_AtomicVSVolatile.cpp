/**
 * @brief std::atomic vs volatile
 *
 */
#include "../../common.hpp"

#include <atomic>

std::atomic<bool> atomic_flag{false};
bool announce_flag_1{false};

void foo() {
    // Guaranteed that NO thread will see announce_flag_1 == true BEFORE atomic_flag.load() == true
    // This happens thanks to std::memory_order::seq_cst (sequential memory order) wich gives
    // guarantee: No other thread will see after-state before atomic operation takes place
    atomic_flag.store(true);
    announce_flag_1 = true;
}

volatile bool flag{false};
volatile bool announce_flag_2{false};

void bar() {
    // No Guarantees at all. Compiler can reorder these lines as it wants
    // (volatile restricts order only for variable it qualifies)
    flag = true;
    announce_flag_2 = true;
}

int main() {}