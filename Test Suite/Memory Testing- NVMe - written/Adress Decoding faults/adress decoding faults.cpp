#include <iostream>
#include <cstdint>
#include <cassert>

//  simple memory map 
#define MEM_SIZE 0x10000 // 64KB
uint8_t memory[MEM_SIZE];

//  write data to memory
void write_memory(uintptr_t address, uint8_t data) {
    if (address >= MEM_SIZE) {
        std::cerr << "Error: Address out of range: 0x" << std::hex << address << std::endl;
        assert(false); 
    }
    memory[address] = data;
}

// read data from memory
uint8_t read_memory(uintptr_t address) {
    if (address >= MEM_SIZE) {
        std::cerr << "Error: Address out of range: 0x" << std::hex << address << std::endl;
        assert(false); 
    }
    return memory[address];
}

int main() {
    std::cout << "Starting Address Decoding Test..." << std::endl;


    // Write and read at the beginning of memory
    uintptr_t address1 = 0x0000;
    uint8_t data1_write = 0xAA;
    write_memory(address1, data1_write);
    uint8_t data1_read = read_memory(address1);
    assert(data1_read == data1_write);
    std::cout << "Test Case 1 Passed: Start of Memory" << std::endl;

    //  Write and read at the end of memory
    uintptr_t address2 = MEM_SIZE - 1;
    uint8_t data2_write = 0xBB;
    write_memory(address2, data2_write);
    uint8_t data2_read = read_memory(address2);
    assert(data2_read == data2_write);
    std::cout << "Test Case 2 Passed: End of Memory" << std::endl;

    // Write and read in the middle of memory
    uintptr_t address3 = MEM_SIZE / 2;
    uint8_t data3_write = 0xCC;
    write_memory(address3, data3_write);
    uint8_t data3_read = read_memory(address3);
    assert(data3_read == data3_write);
    std::cout << "Test Case 3 Passed: Middle of Memory" << std::endl;

    // Multiple writes and reads to different locations
    uintptr_t address4 = 0x1234;
    uint8_t data4_write = 0xDD;
    write_memory(address4, data4_write);

    uintptr_t address5 = 0x5678;
    uint8_t data5_write = 0xEE;
    write_memory(address5, data5_write);

    uint8_t data4_read = read_memory(address4);
    uint8_t data5_read = read_memory(address5);
    assert(data4_read == data4_write);
    assert(data5_read == data5_write);
    std::cout << "Test Case 4 Passed: Multiple Locations" << std::endl;



    std::cout << "All Address Decoding Tests Passed!" << std::endl;

    return 0;
}