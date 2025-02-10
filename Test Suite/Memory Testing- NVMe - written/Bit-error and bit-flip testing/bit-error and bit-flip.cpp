#include <iostream>
#include <vector>
#include <cstdint>
#include <random>
#include <algorithm>

// simulate memory read/write 
bool simulate_memory_access(uint8_t* memory, size_t address, uint8_t write_data, bool write_enable) {
    if (address >= 1024) return false; // Simulate memory boundary

    if (write_enable) {
        memory[address] = write_data;
    } 
    return true; // Simulate successful access
}

int main() {
    const size_t memory_size = 1024; // Example memory size
    uint8_t memory[memory_size] = {0}; // Initialize memory

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 255); 

    int errors = 0;

    for (int i = 0; i < 1000; ++i) { // Run many tests
        size_t address = static_cast<size_t>(distrib(gen)) % memory_size; 
        uint8_t write_data = static_cast<uint8_t>(distrib(gen)); 

        // Write to memory
        if (!simulate_memory_access(memory, address, write_data, true)) {
          std::cerr << "Memory write failed at address: " << address << std::endl;
          return 1; 
        }

        // Read from memory
        uint8_t read_data;
        if (!simulate_memory_access(memory, address, 0, false)) {
          std::cerr << "Memory read failed at address: " << address << std::endl;
          return 1; 
        }
        read_data = memory[address];


        // Check for bit flips (errorfds)

        if (read_data != write_data) {
            std::cerr << "Bit error detected at address: " << address << std::endl;
            std::cerr << "Expected: " << static_cast<int>(write_data) << ", Read: " << static_cast<int>(read_data) << std::endl;
            errors++;

            //check which bits flipped:
            for (int j = 0; j < 8; ++j) {
                if (((read_data >> j) & 1) != ((write_data >> j) & 1)) {
                    std::cerr << "Bit " << j << " flipped." << std::endl;
                }
            }
        }
    }

    if (errors == 0) {
        std::cout << "No bit errors detected." << std::endl;
    } else {
        std::cout << "Total bit errors detected: " << errors << std::endl;
    }

    return 0;
}