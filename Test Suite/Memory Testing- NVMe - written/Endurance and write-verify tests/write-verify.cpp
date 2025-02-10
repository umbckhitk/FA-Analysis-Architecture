#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <cassert>

const size_t MEMORY_SIZE = 1024 * 1024; 
const size_t ITERATIONS = 1000000;      
const size_t VERIFICATION_INTERVAL = 1000; 

// generate random data
std::vector<uint8_t> generateRandomData(size_t size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 255);

    std::vector<uint8_t> data(size);
    for (size_t i = 0; i < size; ++i) {
        data[i] = distrib(gen);
    }
    return data;
}

int main() {
    std::cout << "Starting Endurance and Write-Verify Test..." << std::endl;

    // Allocate memory 
    std::vector<uint8_t> memory(MEMORY_SIZE);  
                                           

    auto start_time = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < ITERATIONS; ++i) {
        std::vector<uint8_t> data = generateRandomData(MEMORY_SIZE);

        for (size_t j = 0; j < MEMORY_SIZE; ++j) {
            memory[j] = data[j]; 
        }

        if (i % VERIFICATION_INTERVAL == 0) {
            for (size_t j = 0; j < MEMORY_SIZE; ++j) {
                assert(memory[j] == data[j]); 
                if (memory[j]!= data[j]) {
                    std::cerr << "Verification failed at iteration " << i << ", address " << j << std::endl;
                    return 1; 
                }
            }
            std::cout << "Verification passed at iteration " << i << std::endl; 
        }

        if ((i+1) % (ITERATIONS/10) == 0) { // 10%
            auto current_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time);
            std::cout << (i + 1) * 100 / ITERATIONS << "% complete. Elapsed time: " << duration.count()/1000.0 << " seconds." << std::endl;
        }

    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout << "Endurance test completed successfully." << std::endl;
    std::cout << "Total elapsed time: " << duration.count() / 1000.0 << " seconds" << std::endl;

    return 0;
}