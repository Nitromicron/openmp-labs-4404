#include <iostream>
#include <cstdlib>
#include <omp.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <num_threads>\n";
        return 1;
    }

    int num_threads = std::atoi(argv[1]);
    omp_set_num_threads(num_threads);

#pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int total = omp_get_num_threads();
        std::cout << "Hello World from thread " << tid
            << " of " << total << std::endl;
    }

    return 0;
}