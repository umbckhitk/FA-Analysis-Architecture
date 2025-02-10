#include <iostream>
#include <cstdint>
#include <vector>
#include <random>
#include <cassert>

class SimulatedMemory {
public:
    SimulatedMemory(size_t size) : memory_(size, 0) {}

    void write(uintptr_t address, uint32_t data) {
        if (address < memory_.size()) {
            memory_[address] = data;
        } else {
            std::cerr << "Error: Memory access out of bounds (write)" << std::endl;
            assert(false); 
        }
    }

    uint32_t read(uintptr_t address) const {
        if (address < memory_.size()) {
            return memory_[address];
        } else {
            std::cerr << "Error: Memory access out of bounds (read)" << std::endl;
            assert(false); 
            return 0; 
        }
    }

private:
    std::vector<uint32_t> memory_;
};


bool powerUpTest(SimulatedMemory& memory, size_t num_locations_to_test = 1024) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, memory.memory_.size() - 1); 
    std::uniform_int_distribution<uint32_t> data_distrib(0, UINT32_MAX); 


    std::cout << "Starting Power-Up Memory Test..." << std::endl;

  
    for (size_t i = 0; i < num_locations_to_test; ++i) {
        uintptr_t address = distrib(gen);
        uint32_t data_to_write = data_distrib(gen);

        memory.write(address, data_to_write);
        uint32_t data_read = memory.read(address);

        if (data_read != data_to_write) {
            std::cerr << "Error: Data mismatch at address 0x" << std::hex << address << std::dec << std::endl;
            std::cerr << "Expected: 0x" << std::hex << data_to_write << std::dec << ", Read: 0x" << std::hex << data_read << std::dec << std::endl;
            return false;
        }
    }

    std::cout << "Power-Up Memory Test Passed." << std::endl;
    return true;
}

int main() {
    size_t memory_size = 1024 * 1024; 
    SimulatedMemory memory(memory_size);

    if (powerUpTest(memory)) {
        return 0; 
    } else {
        return 1; 
    }
}