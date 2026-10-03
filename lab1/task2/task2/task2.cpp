#include <iostream>
#include <cstdlib>
#include <cstring>
#include <omp.h>

#define N 16000

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <num_threads> <schedule>\n";
        std::cout << "schedule: static | dynamic | guided | runtime\n";
        return 1;
    }

    int num_threads = std::atoi(argv[1]);
    const char* schedule = argv[2];

    omp_set_num_threads(num_threads);

    if (std::strcmp(schedule, "static") == 0)
        _putenv((char*)"OMP_SCHEDULE=static");
    else if (std::strcmp(schedule, "dynamic") == 0)
        _putenv((char*)"OMP_SCHEDULE=dynamic");
    else if (std::strcmp(schedule, "guided") == 0)
        _putenv((char*)"OMP_SCHEDULE=guided");
    else
        _putenv((char*)"OMP_SCHEDULE=runtime");

    double* a = new double[N];
    double* b = new double[N];

    for (int i = 0; i < N; i++) {
        a[i] = static_cast<double>(i);
    }

    double start = omp_get_wtime();

    #pragma omp parallel for schedule(runtime)
    for (int i = 1; i < N - 1; i++) {
        b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
    }

    double end = omp_get_wtime();

    std::cout << "b[1] = " << b[1] << std::endl;
    std::cout << "b[100] = " << b[100] << std::endl;
    std::cout << "b[N-2] = " << b[N - 2] << std::endl;
    std::cout << "Time = " << (end - start) << " sec (threads = "
        << num_threads << ", schedule = " << schedule << ")\n";

    delete[] a;
    delete[] b;
    return 0;
}