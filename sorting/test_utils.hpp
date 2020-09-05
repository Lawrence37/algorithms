#pragma once

#include <random>
#include <vector>


/**
 * Checks if the list is sorted in ascending order.
 *
 * @param front A random access iterator to the front of the list.
 * @param back A random access iterator to the back of the list.
 * @return Whether the list is sorted or not.
 */
template<class RandAccessIterator>
bool isSorted(RandAccessIterator front, RandAccessIterator back) {
    auto current = front;
    auto next = front + 1;

    for (; next < back; ++current, ++next) {
        if (*current > *next) {
            return false;
        }
    }

    return true;
}

/**
 * Creates a list of random ints.
 *
 * @param size The list size.
 * @return The list.
 */
std::vector<int> randomIntList(size_t size) {
    std::vector<int> list(size);

    std::default_random_engine r_engine;
    std::uniform_int_distribution<int> r_distr;

    for (size_t i = 0; i < size; ++i) {
        list[i] = r_distr(r_engine);
    }

    return list;
}
