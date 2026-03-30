#ifndef MATH_LIB_H
#define MATH_LIB_H
struct MonteResult {
    double volume;
    double time;
};
extern "C" {
    const char* get_info();
    void calc_sphere(int n, MonteResult* res);
}
#endif
