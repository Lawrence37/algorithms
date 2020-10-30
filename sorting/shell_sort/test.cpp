#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

#include "../../test_utils.hpp"
#include "../test_utils.hpp"
#include "../insertion_sort/insertion_sort.hpp"
#include "shell_sort.hpp"


template<typename T1, typename T2>
void printRow(T1 a, T2 b, T2 c) {
    constexpr int n_width = 10;
    constexpr int time_precision = 8;
    constexpr int time_width = 12;
    std::cout
            << std::fixed
            << std::setw(n_width) << a
            << std::setw(time_width) << std::setprecision(time_precision) << b
            << std::setw(time_width) << std::setprecision(time_precision) << c
            << std::endl;
}

int main() {
    std::vector<int> sort_me = randomIntList(1000);

    // Test correctness.
    assert(!isSorted(sort_me.cbegin(), sort_me.cend()));
    shellSort(sort_me.begin(), sort_me.end());
    assert(isSorted(sort_me.cbegin(), sort_me.cend()));

    // Test speed.
    printRow("n", "sort()", "shellSort()");
    for (long n : {0, 1, 10, 100, 1000, 10000, 100000, 1000000}) {
        std::vector<int> unsorted = randomIntList(n);

        double shellSort_time = time([unsorted]() mutable {
                shellSort(unsorted.begin(), unsorted.end());
                });

        double sort_time = time([unsorted]() mutable {
                std::sort(unsorted.begin(), unsorted.end());
                });

        printRow(n, sort_time, shellSort_time);
    }

    return 0;
}
