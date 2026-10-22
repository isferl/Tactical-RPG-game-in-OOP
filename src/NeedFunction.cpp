#include "../include/NeedFunction.h"
#include <random>

int get_random_number(int a, int b) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution distrib(a, b);
    return distrib(gen);
}


int distance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}
