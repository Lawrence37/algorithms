#pragma once

#include <iterator>


/**
 * Performs insertion sort on a list.
 *
 * @param front A random access iterator to the front of the list.
 * @param back A random access iterator to the back of the list.
 */
template<class RandAccessIterator>
void insertionSort(RandAccessIterator front, RandAccessIterator back) {
    using value_type =
            typename std::iterator_traits<RandAccessIterator>::value_type;

    // Build up the sorted list, one item at a time.
    for (auto unsorted = front + 1; unsorted < back; ++unsorted) {
        const value_type tmp_value = *unsorted; // The next value to insert.
        auto insert_index_min = front;
        auto insert_index_max = unsorted;

        // Perform binary search to find where to insert the next value.
        while (insert_index_min != insert_index_max) {
            const auto insert_index_middle =
                    insert_index_min
                    + (insert_index_max - insert_index_min) / 2;
            if (*insert_index_middle <= tmp_value) {
                insert_index_min = insert_index_middle + 1;
            } else {
                insert_index_max = insert_index_middle;
            }
        }

        // Make room for the new value.
        for (
            auto shift_index = unsorted;
            shift_index > insert_index_min;
            --shift_index
        ) {
            *shift_index = *(shift_index - 1);
        }

        // Finally, insert the value.
        *insert_index_min = tmp_value;
    }
}
