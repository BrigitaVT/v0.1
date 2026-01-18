#include "Skaiciavimai.h"
#include <algorithm>

double vidurkis(const std::vector<int>& v) {
    double s = 0;
    for (int x : v) s += x;
    return s / v.size();
}

double mediana(std::vector<int> v) {
    std::sort(v.begin(), v.end());
    int n = v.size();
    if (n % 2) return v[n / 2];
    return (v[n / 2 - 1] + v[n / 2]) / 2.0;
}

