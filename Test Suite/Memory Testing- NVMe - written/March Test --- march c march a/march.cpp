#include <iostream>
#include <vector>
#include <cassert>

class Memory {
public:
    Memory(size_t size) : size_(size), data_(size, 0) {}

    uint8_t read(size_t address) const {
        assert(address < size_);
        return data_[address];
    }

    void write(size_t address, uint8_t value) {
        assert(address < size_);
        data_[address] = value;
    }

private:
    size_t size_;
    std::vector<uint8_t> data_;
};


bool march_c_test(Memory& memory) {
    size_t size = memory.size();

    // March C- Algorithm
    for (size_t i = 0; i < size; ++i) {
        memory.write(i, 0);  
    }
    for (size_t i = 0; i < size; ++i) {
        if (memory.read(i) != 0) return false; 
    }
    for (size_t i = 0; i < size; ++i) {
        memory.write(i, 1); //  1
    }
    for (size_t i = 0; i < size; ++i) {
        if (memory.read(i) != 1) return false; //  1??
    }
    for (size_t i = size; i > 0; --i) { 
        memory.write(i-1, 0); //  0
    }
    for (size_t i = size; i > 0; --i) { 
        if (memory.read(i-1) != 0) return false; //  0??
    }
    for (size_t i = size; i > 0; --i) { 
        memory.write(i-1, 1); //  1
    }
    for (size_t i = size; i > 0; --i) { 
        if (memory.read(i-1) != 1) return false; //  1??
    }

    return true;
}


int main() {
    size_t memory_size = 256; 
    Memory memory(memory_size);

    if (march_c_test(memory)) {
        std::cout << "March C- test passed!" << std::endl;
    } else {
        std::cout << "March C- test failed!" << std::endl;
        return 1; 
    }

    return 0; 
}