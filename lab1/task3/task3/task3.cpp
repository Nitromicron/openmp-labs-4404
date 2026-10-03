#include <iostream>
#include <cstdlib>
#include <omp.h>
#include <thread>
#include <chrono>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <num_threads> <method 1-5>\n";
        return 1;
    }

    int num_threads = std::atoi(argv[1]);
    int method = std::atoi(argv[2]);
    omp_set_num_threads(num_threads);

    std::cout << "=== Method " << method << " ===" << std::endl;

    switch (method) {

        // Метод 1
    case 1:
#pragma omp parallel
    {
#pragma omp for ordered schedule(static)
        for (int i = 0; i < num_threads; i++) {
            int real = num_threads - 1 - i;
#pragma omp ordered
            {
                std::cout << "Thread " << real << " of " << num_threads << std::endl << std::flush;
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        }
    }
    break;

    // Метод 2
    case 2:
#pragma omp parallel
    {
        int tid = omp_get_thread_num();
        for (int i = num_threads - 1; i >= 0; i--) {
#pragma omp barrier
            if (tid == i) {
#pragma omp critical
                {
                    std::cout << "Thread " << tid << " of " << num_threads << std::endl << std::flush;
                }
            }
        }
    }
    break;

    // Метод 3
    case 3:
#pragma omp parallel
    {
#pragma omp single
        {
            for (int i = num_threads - 1; i >= 0; i--) {
                std::cout << "Thread " << i << " of " << num_threads << std::endl << std::flush;
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        }
    }
    break;

    // Метод 4
    case 4:
    {
        int next = num_threads - 1;
#pragma omp parallel shared(next)
        {
            int tid = omp_get_thread_num();
            while (true) {
                bool should_print = false;
#pragma omp critical
                {
                    if (next == tid) {
                        should_print = true;
                        next--;
                    }
                }
                if (should_print) {
#pragma omp critical
                    {
                        std::cout << "Thread " << tid << " of " << num_threads << std::endl << std::flush;
                    }
                }
                if (next < 0) break;
            }
        }
        break;
    }

    // Метод 5
    case 5:
#pragma omp parallel
    {
#pragma omp for schedule(static, 1) ordered
        for (int i = 0; i < num_threads; i++) {
            int real = num_threads - 1 - i;
#pragma omp ordered
            {
                std::cout << "Thread " << real << " of " << num_threads << std::endl << std::flush;
            }
        }
    }
    break;

    default:
        std::cout << "Unknown method\n";
        break;
    }

    return 0;
}