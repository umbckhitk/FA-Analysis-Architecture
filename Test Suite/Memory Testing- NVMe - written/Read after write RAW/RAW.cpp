#include <iostream>
#include <cassert>
#include <cstdint> 

bool raw_test(volatile uint8_t* memory, size_t size) {

    for (size_t i = 0; i < size; ++i) {
        for (uint8_t data = 0; data < 256; data += 64) { 
            memory[i] = data; 
            uint8_t read_data = memory[i]; 

            if (read_data!= data) {
                std::cerr << "RAW error at address 0x" << std::hex << reinterpret_cast<uintptr_t>(&memory[i]) << ": "
                          << "Expected 0x" << std::hex << static_cast<int>(data) << ", got 0x" << static_cast<int>(read_data) << std::dec << std::endl;
                return false; 
            }
        }
    }


   
    return true; 
}

int main() {
   //registers ---- extra 
    const size_t memory_size = 1024; 
    uint8_t* test_memory = new uint8_t[memory_size];  
                                                    

    if (raw_test(test_memory, memory_size)) {
        std::cout << "Read-After-Write test passed." << std::endl;
    } else {
        std::cout << "Read-After-Write test failed." << std::endl;
    }

    delete test_memory; 

    return 0;
}