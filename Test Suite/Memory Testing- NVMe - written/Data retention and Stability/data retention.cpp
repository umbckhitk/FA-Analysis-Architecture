#include <iostream>
#include <vector>
#include <cstdint>
#include <random>
#include <chrono>

class Memory {
public:
    Memory(size_t size) : data_(size) {}

    void write(uintptr_t address, uint8_t value) {
        if (address < data_.size()) {
            data_[address] = value;
        } else {
            std::cerr << "Error: Address out of range" << std::endl;
        }
    }

    uint8_t read(uintptr_t address) const {
        if (address < data_.size()) {
            return data_[address];
        } else {
            std::cerr << "Error: Address out of range" << std::endl;
            return 0;
        }
    }

    void powerCycle() {
        std::cout << "Simulating power cycle" << std::endl;
     
    }

    void reset() {
        std::cout << "Simulating reset" << std::endl;
        
    }

private:
    std::vector<uint8_t> data_;
};


bool testDataRetention(Memory& memory, size_t numWrites) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 255); 
    std::uniform_int_distribution<> addrDist(0, memory.data_.size() -1); 

    std::cout << "Writing data..." << std::endl;
    std::vector<std::pair<uintptr_t, uint8_t>> writtenData; // Store 

    for (size_t i = 0; i < numWrites; ++i) {
      uintptr_t address = addrDist(gen);
      uint8_t value = distrib(gen);
      memory.write(address, value);
      writtenData.push_back({address, value});
    }


    // Choose either power cycle or reset for the test
    // memory.powerCycle();
    memory.reset();


    std::cout << "Verifying data..." << std::endl;
    bool allDataRetained = true;
    for (const auto& [address, expectedValue] : writtenData) {
        uint8_t readValue = memory.read(address);
        if (readValue != expectedValue) {
            std::cerr << "Error: Data mismatch at address " << address
                      << ". Expected " << static_cast<int>(expectedValue)
                      << ", got " << static_cast<int>(readValue) << std::endl;
            allDataRetained = false;
        }
    }

    return allDataRetained;
}

int main() {
    
    size_t memorySize = 1024 * 1024;  // 1MB
    Memory memory(memorySize);
    size_t numWrites = 10000; 

    if (testDataRetention(memory, numWrites)) {
        std::cout << "Data retention test passed." << std::endl;
    } else {
        std::cout << "Data retention test failed." << std::endl;
    }

    return 0;
}