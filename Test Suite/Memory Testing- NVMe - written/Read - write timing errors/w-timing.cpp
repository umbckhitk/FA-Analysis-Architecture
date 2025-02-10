#include <iostream>
#include <chrono>
#include <cstdint>
#include <cstdlib> // For rand() and srand()

// Define a simple memory interface (replace with your actual memory access methods)
class Memory {
public:
    Memory(size_t size) : size_(size) {
        data_ = new uint8_t[size];
    }

    ~Memory() {
        delete[] data_;
    }

    bool read(uintptr_t address, uint8_t& value) {
        if (address >= size_) {
            std::cerr << "Error: Read out of bounds" << std::endl;
            return false;
        }
        value = data_[address];
        return true;
    }

    bool write(uintptr_t address, uint8_t value) {
        if (address >= size_) {
            std::cerr << "Error: Write out of bounds" << std::endl;
            return false;
        }
        data_[address] = value;
        return true;
    }

private:
    uint8_t* data_;
    size_t size_;
};


bool test_read_write_timing(Memory& memory, int num_iterations, int min_delay_ns, int max_delay_ns) {
    srand(time(0)); 

    for (int i = 0; i < num_iterations; ++i) {
        uintptr_t address = rand() % (memory.size() - 1); 
        uint8_t write_value = rand() % 256; 
        uint8_t read_value;

        // Write
        if (!memory.write(address, write_value)) {
            return false; 
        }

        // random delay -clock cycles)
        int delay_ns = rand() % (max_delay_ns - min_delay_ns + 1) + min_delay_ns;
        std::this_thread::sleep_for(std::chrono::nanoseconds(delay_ns));

        // Read
        if (!memory.read(address, read_value)) {
            return false; 
        }

        // Verify data
        if (read_value != write_value) {
            std::cerr << "Error: Read value mismatch at address " << address << std::endl;
            return false; 
        }

        auto start = std::chrono::high_resolution_clock::now();
        if (!memory.read(address, read_value)) {
            return false;
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        if(duration > (max_delay_ns*2)) {
            std::cerr << "Error: Read time exceeded expectations at address " << address << std::endl;
            return false;
        }


    }

    return true; // Test passed
}

int main() {
    size_t memory_size = 1024 * 1024; // 1MB
    Memory memory(memory_size);

    int num_iterations = 10000;
    int min_delay_ns = 100; 
    int max_delay_ns = 1000; 

    if (test_read_write_timing(memory, num_iterations, min_delay_ns, max_delay_ns)) {
        std::cout << "Read/Write timing test passed." << std::endl;
    } else {
        std::cout << "Read/Write timing test failed." << std::endl;
    }

    return 0;
}