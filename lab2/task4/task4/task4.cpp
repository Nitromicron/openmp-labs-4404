#include <iostream>
#include <cstdlib>
#include <omp.h>
#include <ctime>

void matmul_seq(double* A, double* B, double* C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double sum = 0.0;
            for (int k = 0; k < n; k++) {
                sum += A[i * n + k] * B[k * n + j];
            }
            C[i * n + j] = sum;
        }
    }
}

void matmul_par(double* A, double* B, double* C, int n) {
#pragma omp parallel for
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double sum = 0.0;
            for (int k = 0; k < n; k++) {
                sum += A[i * n + k] * B[k * n + j];
            }
            C[i * n + j] = sum;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <matrix_size> <num_threads>\n";
        return 1;
    }

    int n = std::atoi(argv[1]);
    int num_threads = std::atoi(argv[2]);
    omp_set_num_threads(num_threads);

    double* A = new double[n * n];
    double* B = new double[n * n];
    double* C = new double[n * n];

    std::srand(42);
    for (int i = 0; i < n * n; i++) {
        A[i] = (std::rand() % 100) / 10.0;
        B[i] = (std::rand() % 100) / 10.0;
    }

    double t0 = omp_get_wtime();
    matmul_seq(A, B, C, n);
    double t_seq = omp_get_wtime() - t0;

    t0 = omp_get_wtime();
    matmul_par(A, B, C, n);
    double t_par = omp_get_wtime() - t0;

    std::cout << "Matrix size: " << n << " x " << n << std::endl;
    std::cout << "Threads: " << num_threads << std::endl;
    std::cout << "Sequential time: " << t_seq << " sec\n";
    std::cout << "Parallel time:   " << t_par << " sec\n";
    std::cout << "Speedup:         " << (t_seq / t_par) << "x\n";

    delete[] A;
    delete[] B;
    delete[] C;
    return 0;
}