#include <iostream>
#include <random>
#include <omp.h>

void merge(intptr_t* arr,  intptr_t a, intptr_t c,  intptr_t b) {
    const intptr_t N1 = c - a + 1;
    const intptr_t N2 = b - c;

    intptr_t* l_arr = new intptr_t[N1];
    intptr_t* r_arr = new intptr_t[N2];

    for (intptr_t i = 0; i < N1; i++) {
        l_arr[i] = arr[a + i];
    }

    for (intptr_t j = 0; j < N2; j++) {
        r_arr[j] = arr[c + 1 + j];
    }

    intptr_t i = 0, j = 0, k = a;

    while (i < N1 && j < N2) {
        if (l_arr[i] <= r_arr[j]) {
            arr[k] = l_arr[i];
            i++;
        }
        else {
            arr[k] = r_arr[j];
            j++;
        }
        k++;
    }

    while (i < N1) {
        arr[k] = l_arr[i];
        i++;
        k++;
    }

    while (j < N2) {
        arr[k] = r_arr[j];
        j++;
        k++;
    }

}

void parallelMergeSort(intptr_t* arr,  intptr_t a,  intptr_t b) {
    if (a >= b)
        return;
    intptr_t m = a + (b - a) / 2;
#pragma omp task
    parallelMergeSort(arr, a, m);
#pragma omp task
    parallelMergeSort(arr, m + 1, b);

    merge(arr, a, m, b);
}

int main() {

    const intptr_t N = 1e6;
    srand(time(NULL));
    intptr_t* arr1 = new intptr_t[N];
    for (intptr_t i = 0; i < N; ++i) {
        arr1[i] = 100 - rand() % 200;
    }

    double start = omp_get_wtime();
#pragma omp parallel
    {
#pragma omp single
        parallelMergeSort(arr1, 0, N - 1);
    }
    double end = omp_get_wtime();
    std::cout << "Time in ms: " << (end - start) * 1000 << std::endl;


    return 0;
}
