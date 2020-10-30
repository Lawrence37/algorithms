#include <vector>

#include "../insertion_sort/insertion_sort.hpp"
#include "../../libraries/skip_iterator.hpp"


namespace {

/**
 * Computes Sedgewick's gap numbers.
 *
 * @param limit The maximum gap needed. Must be at least 1.
 * @return The gap numbers from smallest to largest.
 */
std::vector<long> sedgewickGaps(long limit) {
    std::vector<long> gaps;
    long pow_2 = 1;
    long pow_4 = 1;

    // Sedgewick's numbers alternate between two formulas. Keep calculating them
    // until we meet or exceed the limit.
    do {
        gaps.push_back(9 * (pow_4 - pow_2) + 1);
        gaps.push_back(pow_2 * (16 * pow_2 - 12) + 1);
        pow_2 *= 2;
        pow_4 *= 4;
    } while (gaps.back() < limit);

    // Backtrack if needed.
    while (gaps.back() > limit) {
        gaps.pop_back();
    }

    return gaps;
}

}


/**
 * Perform Shell sort on a list.
 *
 * @param front A random access iterator to the front of the list.
 * @param back A random access iterator to the back of the list.
 */
template<class RandAccessIterator>
void shellSort(RandAccessIterator front, RandAccessIterator back) {
    if (back - front <= 1) {
        return;
    }

    const auto length = back - front;
    const std::vector<long> gaps = sedgewickGaps(length - 1);

    SkipIterator<RandAccessIterator> sub_front, sub_back;
    for (int gap_index = gaps.size() - 1; gap_index >= 0; gap_index--) {
        const auto & gap = gaps[gap_index];
        sub_front.setSpacing(gap);
        sub_back.setSpacing(gap);

        // Perform insertion sort for each possible offset.
        for (int offset = 0; offset < gap; offset++) {
            const auto first_iter = front + offset;
            const auto last_iter =
                first_iter + ((length - 1 - offset) / gap + 1) * gap;
            sub_front.set(first_iter);
            sub_back.set(last_iter);

            insertionSort(sub_front, sub_back);
        }
    }
}
