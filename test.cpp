#include <cstdlib>
#include <omp.h>
#include <vector>
#include <array>
#include <random>
#include <fstream>
#include <chrono>
#include <iostream>
#include <thread>
#include "cyPolynomial.h"


int intRand(const int & min, const int & max) {
    static thread_local std::mt19937 generator;
    std::uniform_int_distribution<int> distribution(min,max);
    return distribution(generator);
}

int main(int argc, char *argv[]){
    const int x = atoi(argv[1]);

    const int numThreads = std::thread::hardware_concurrency();

    std::cout << "Running on " << numThreads << " threads (logical processors)\n";

    omp_set_num_threads(numThreads); 

    auto start = std::chrono::steady_clock::now();

    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < x; i++){

        float coeffs[7];
        float root;

        for (int j = 0; j < 7; j++){
            coeffs[j] = intRand(-1000, 1000) / 10.0f;
        }

        (void)cy::PolynomialFirstRoot<6, float>(root, coeffs);
    }

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Runtime: " << duration.count() << " milliseconds" << std::endl;
}