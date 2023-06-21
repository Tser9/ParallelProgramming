#include <iostream>
#include <omp.h>


int main0() {
    intptr_t n = 1e9;
    intptr_t sum = 0;
    intptr_t* A = new intptr_t[n];
    double start = 0;
    double end = 0;

    for (intptr_t i = 0; i < n; ++i)
        A[i] = i;

 
        std::cout << "Reduction" << std::endl;
        start = omp_get_wtime();

#pragma omp parallel for reduction(+:sum)
        for (intptr_t i = 0; i < n; ++i)
            sum += A[i];
        end = omp_get_wtime();
        std::cout << "Time: " << end - start << std::endl;
        sum = 0;


        std::cout << "Atomic" << std::endl;
        start = omp_get_wtime();
#pragma omp parallel for
        for (intptr_t i = 0; i < n; ++i) {
#pragma omp atomic
            sum += A[i];
        }
        end = omp_get_wtime();
        std::cout << "Time: " << end - start << std::endl;
        sum = 0;


        std::cout << "Sequential" << std::endl;
        start = omp_get_wtime();
        for (intptr_t i = 0; i < n; ++i)
            sum += A[i];
        end = omp_get_wtime();
        std::cout << "Time: " << end - start << std::endl;

    return 0;
}
