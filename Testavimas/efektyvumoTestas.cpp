#include "Vector.h"
#include <vector>
#include <chrono>
#include <iostream>

void testPerformance() {
    const size_t sizes[] = {10000, 100000, 1000000, 10000000, 100000000};
    
    std::cout << "Elementu kiekis | std::vector | Vector\n";
    std::cout << "---------------------------------------\n";
    
    for (size_t sz : sizes) {
        // std::vector testas
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<int> std_vec;
        for (size_t i = 0; i < sz; ++i) {
            std_vec.push_back(i);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto std_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        
        // Vector testas
        start = std::chrono::high_resolution_clock::now();
        Vector<int> my_vec;
        for (size_t i = 0; i < sz; ++i) {
            my_vec.push_back(i);
        }
        end = std::chrono::high_resolution_clock::now();
        auto my_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        std::cout << sz << " | " << std_time*0.001 << " ms | " << my_time*0.001 << " ms | " << "\n";
    }
}

int main() {
    testPerformance();
    return 0;
}