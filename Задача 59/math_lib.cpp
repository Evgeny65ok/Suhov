#include "math_lib.h"
#include <cstdlib>
#include <ctime>
#include <chrono>

extern "C" const char* get_info() { return "Author: Evgeniy Beleviy"; }

extern "C" void calc_sphere(int n, MonteResult* res) {
    auto start = std::chrono::high_resolution_clock::now();
    srand(time(0));
    int k = 0;
    for (int i = 0; i < n; i++) {
        double x = (double)rand()/RAND_MAX*2-1;
        double y = (double)rand()/RAND_MAX*2-1;
        double z = (double)rand()/RAND_MAX*2-1;
        if (x*x + y*y + z*z <= 1) k++;
    }
    res->volume = (double)k / n * 8.0;
    auto end = std::chrono::high_resolution_clock::now();
    res->time = std::chrono::duration<double>(end - start).count();
}
