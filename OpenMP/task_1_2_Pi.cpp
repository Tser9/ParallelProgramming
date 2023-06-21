#include <iostream>
#include <iomanip>
#include <omp.h>

int main() {

    const intptr_t N = 12;
    const intptr_t arr_treads[] = { 1, 2, 4, 8, 10, 12 };
    double x;
    double time[N];
    double result[N];

    for (intptr_t k = 0; k < N; ++k) {
        double pi = .0;
        intptr_t n;
        if (k % 2 == 0)
            n = 1e2;
        else
            n = 1e6;
       

        double start = omp_get_wtime();

#pragma omp parallel for num_threads(treads) private(x), reduction(+:pi)
        for (intptr_t i = 0; i < n; ++i) {
            x = (i + 0.5) / n;
            pi += 4 / (1 + x * x);
        }
        pi /= n;
        double end = omp_get_wtime();
        time[k] = (end - start) * 1000;
    }

   std::cout << "Treads\t";
   std::cout << "N\t";
   std::cout << "Time\t" << std::endl;

    for (intptr_t i = 0; i < N; ++i) {

        std::cout << arr_treads[i / 2];
        std::cout << "\t";
        std::cout << std::setprecision(0)<< (i % 2 == 0 ? 1e2 : 1e6);
        std::cout << "\t";
        std::cout <<std::setprecision(8)<<time[i]<< std::endl;
    }

    return 0;
}
