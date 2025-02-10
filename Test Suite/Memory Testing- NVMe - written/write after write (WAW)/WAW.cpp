#include <iostream>
#include <cassert>
#include <cstdint> 

void write_memory(volatile uint32_t* address, uint32_t value) {
    *address = value;  
}

uint32_t read_memory(volatile uint32_t* address) {
    return *address; 
}

int main() {
    volatile uint32_t test_address = 0x10000000; 

    const int num_writes = 10;

    for (int i = 0; i < num_writes; ++i) {
        uint32_t data_to_write = i * 10 + 5; 
        write_memory(&test_address, data_to_write);
        std::cout << "Write " << i + 1 << ": Wrote " << data_to_write << " to address 0x" << std::hex << (uintptr_t)&test_address << std::endl;
    }

  
    uint32_t expected_final_value = (num_writes - 1) * 10 + 5;
    uint32_t actual_final_value = read_memory(&test_address);

    std::cout << "Read: Value at address 0x" << std::hex << (uintptr_t)&test_address << " is " << actual_final_value << std::endl;

    assert(actual_final_value == expected_final_value);

    if (actual_final_value == expected_final_value) {
        std::cout << "WAW test PASSED!" << std::endl;
    } else {
        std::cout << "WAW test FAILED!" << std::endl;
        std::cout << "Expected: " << expected_final_value << ", Actual: " << actual_final_value << std::endl;
    }


    return 0;
}