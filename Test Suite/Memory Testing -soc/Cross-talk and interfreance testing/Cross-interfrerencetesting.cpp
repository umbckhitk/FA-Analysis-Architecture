#include <iostream>
#include <vector>
#include <cstdint>
#include <cstdlib> 

//  memory model
class Memory {
public:
    Memory(size_t size) : size_(size), data_(size) {
        // all zero
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = 0;
        }
    }

    ~Memory() = default;

    void write(size_t address, uint8_t value) {
        if (address >= size_) {
            throw std::out_of_range("Memory address out of range");
        }
        data_[address] = value;
    }

    uint8_t read(size_t address) const {
        if (address >= size_) {
            throw std::out_of_range("Memory address out of range");
        }
        return data_[address];
    }

private:
    size_t size_;
    std::vector<uint8_t> data_;
};

bool test_crosstalk(Memory& memory, size_t num_cells_to_test) {
    if (num_cells_to_test > memory.size()) {
        std::cerr << "Error: Number of cells to test exceeds memory size." << std::endl;
        return false;
    }

    
    srand(time(0));

    // Write random data to adjacent memory cells
    std::vector<size_t> test_addresses;
    for (size_t i = 0; i < num_cells_to_test; ++i) {
        test_addresses.push_back(rand() % (memory.size() - num_cells_to_test)); 
        //  out of bounds
    }


    std::vector<uint8_t> original_data(num_cells_to_test);

    for (size_t i = 0; i < num_cells_to_test; ++i) {
      original_data[i] =  rand() % 256; 
      memory.write(test_addresses[i] + i, original_data[i]); 
    }


    // Verify - other cells 
    for (size_t i = 0; i < memory.size(); ++i) {
        bool is_test_address = false;
        for (size_t j = 0; j < num_cells_to_test; j++) {
            if (i >= test_addresses[j] && i < test_addresses[j] + num_cells_to_test) {
                is_test_address = true;
                break;
            }
        }
        if (!is_test_address) { // Check only cells NOT part of the test
            if (memory.read(i) != 0) { // Assuming  value  0
                std::cerr << "Crosstalk detected at address: " << i << std::endl;
                return false;
            }
        } else { // Verify written data
            for (size_t j = 0; j < num_cells_to_test; ++j) {
                if (i == test_addresses[j] + j) {
                    if (memory.read(i) != original_data[j]) {
                        std::cerr << "Data mismatch at address: " << i << std::endl;
                        return false;
                    }
                }
            }
        }
    }

    return true; 
}

int main() {
    size_t memory_size = 1024; 
    Memory memory(memory_size);

    size_t num_cells_to_test = 4; // Test interference between 4 adjacent cells

    if (test_crosstalk(memory, num_cells_to_test)) {
        std::cout << "Crosstalk test passed." << std::endl;
    } else {
        std::cout << "Crosstalk test failed." << std::endl;
    }

    return 0;
}