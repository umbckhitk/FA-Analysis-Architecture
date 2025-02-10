#include <iostream>
#include <vector>
#include <cstdint>
#include <cassert>

//  memory
void write_pattern(uint8_t* memory, size_t size, uint8_t pattern) {
    for (size_t i = 0; i < size; ++i) {
        memory[i] = pattern;
    }
}

// verify a pattern
bool verify_pattern(const uint8_t* memory, size_t size, uint8_t pattern) {
    for (size_t i = 0; i < size; ++i) {
        if (memory[i] != pattern) {
            return false; 
        }
    }
    return true; 
}

int main() {
    size_t memory_size = 1024; 
    uint8_t* memory = new uint8_t[memory_size];  

   
    std::vector<uint8_t> patterns = {0x00, 0xFF, 0xAA, 0x55, 0x0F, 0xF0}; 

    std::cout << "Starting Data Pattern Test..." << std::endl;

    for (uint8_t pattern : patterns) {
        std::cout << "Testing pattern: 0x" << std::hex << std::uppercase << static_cast<int>(pattern) << std::dec << std::endl;

        write_pattern(memory, memory_size, pattern);

        if (verify_pattern(memory, memory_size, pattern)) {
            std::cout << "Pattern verification passed." << std::endl;
        } else {
            std::cerr << "Pattern verification FAILED!" << std::endl;

            for (size_t i = 0; i < std::min((size_t)10, memory_size); ++i) { // Show up to 10 errors
              if (memory[i] != pattern) {
                std::cerr << "Mismatch at address " << i << ": Expected 0x" << std::hex << static_cast<int>(pattern)
                          << ", Actual 0x" << static_cast<int>(memory[i]) << std::dec << std::endl;
              }
            }
            delete[] memory;  
            return 1; 
        }
    }

    std::cout << "Data Pattern Test Completed." << std::endl;

    delete[] memory; 
    return 0; 
}