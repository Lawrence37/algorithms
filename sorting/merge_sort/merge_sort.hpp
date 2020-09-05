#pragma once

#include <iterator>
#include <memory>

#include "../insertion_sort/insertion_sort.hpp"


namespace {

/**
 * Merges two sorted arrays into one.
 *
 * This function is written to be easily understandable and is not optimized.
 *
 * @param array Pointer to the front of the array.
 * @param split Position where the two arrays meet, equal to the length of the
 * first array.
 * @param length The total length of the two arrays.
 */
void merge(int * array, const unsigned long split, const unsigned long length) {
    std::unique_ptr<int[]> buffer(new int[length]);
    int * merged = buffer.get();

    const int * left = array;
    const int * right = array + split;
    const int * const left_end = right;
    const int * const right_end = array + length;

    // Merge the arrays until one array is completely processed.
    while (left < left_end && right < right_end) {
        if (*left < *right) {
            // Left array has the smallest value, so take from the left.
            *merged = *left;
            ++merged;
            ++left;
        } else {
            // Right array has the smallest value, so take from the right.
            *merged = *right;
            ++merged;
            ++right;
        }
    }

    // Dump the remainder of the unprocessed array into the merged array.
    if (left < left_end) {
        while (left < left_end) {
            *merged = *left;
            ++merged;
            ++left;
        }
    } else {
        while (right < right_end) {
            *merged = *right;
            ++merged;
            ++right;
        }
    }

    // Transfer the merged array from the buffer to the origin.
    for (unsigned long i = 0; i < length; ++i) {
        array[i] = buffer[i];
    }
}

/**
 * Merge two lists from the buffer to the origin.
 *
 * @see merge(RandAccessIterator, typename std::iterator_traits<RandAccessIterator>::value_type *, typename std::iterator_traits<RandAccessIterator>::difference_type, typename std::iterator_traits<RandAccessIterator>::difference_type, bool, bool)
 */
template<class RandAccessIterator>
void mergeBufferBuffer(
    RandAccessIterator front,
    typename std::iterator_traits<RandAccessIterator>::value_type * buffer,
    typename std::iterator_traits<RandAccessIterator>::difference_type middle,
    typename std::iterator_traits<RandAccessIterator>::difference_type length
) {
    auto left = buffer;
    auto left_end = buffer + middle;
    auto right = left_end;
    auto right_end = buffer + length;

    // Merge the lists until one list is completely processed.
    while (true) {
        if (*left < *right) {
            *front = *left;
            ++front;
            ++left;
            if (left >= left_end) {
                break;
            }
        } else {
            *front = *right;
            ++front;
            ++right;
            if (right >= right_end) {
                break;
            }
        }
    }

    // Dump the remainder of the first list into the merged list.
    while (left < left_end) {
        *front = *left;
        ++front;
        ++left;
    }

    // Dump the remainder of the second list into the merged list.
    while (right < right_end) {
        *front = *right;
        ++front;
        ++right;
    }
}

/**
 * Merge two lists, the first in the buffer and the second in the origin, to the
 * origin.
 *
 * @see merge(RandAccessIterator, typename std::iterator_traits<RandAccessIterator>::value_type *, typename std::iterator_traits<RandAccessIterator>::difference_type, typename std::iterator_traits<RandAccessIterator>::difference_type, bool, bool)
 */
template<class RandAccessIterator>
void mergeBufferList(
    RandAccessIterator front,
    typename std::iterator_traits<RandAccessIterator>::value_type * buffer,
    typename std::iterator_traits<RandAccessIterator>::difference_type middle,
    typename std::iterator_traits<RandAccessIterator>::difference_type length
) {
    auto left = buffer;
    auto left_end = buffer + middle;
    auto right = front + middle;
    auto right_end = front + length;

    // Merge the lists until one list is completely processed.
    while (true) {
        if (*left < *right) {
            *front = *left;
            ++front;
            ++left;
            if (left >= left_end) {
                break;
            }
        } else {
            *front = *right;
            ++front;
            ++right;
            if (right >= right_end) {
                break;
            }
        }
    }

    // Dump the remainder of the first list into the merged list.
    while (left < left_end) {
        *front = *left;
        ++front;
        ++left;
    }

    // Dump the remainder of the second list into the merged list.
    while (right < right_end) {
        *front = *right;
        ++front;
        ++right;
    }
}

/**
 * Merge two lists, the first in the origin and the second in the buffer, to the
 * origin.
 *
 * @see merge(RandAccessIterator, typename std::iterator_traits<RandAccessIterator>::value_type *, typename std::iterator_traits<RandAccessIterator>::difference_type, typename std::iterator_traits<RandAccessIterator>::difference_type, bool, bool)
 */
template<class RandAccessIterator>
void mergeListBuffer(
    RandAccessIterator front,
    typename std::iterator_traits<RandAccessIterator>::value_type * buffer,
    typename std::iterator_traits<RandAccessIterator>::difference_type middle,
    typename std::iterator_traits<RandAccessIterator>::difference_type length
) {
    // This function works backwards to avoid overwriting the origin.

    auto list_back = front + length - 1;
    auto left = front + middle - 1;
    auto left_end = front;
    auto right = buffer + length - 1;
    auto right_end = buffer + middle;

    // Merge the lists until one list is completely processed.
    while (true) {
        if (*left > *right) {
            *list_back = *left;
            --list_back;
            --left;
            if (left < left_end) {
                break;
            }
        } else {
            *list_back = *right;
            --list_back;
            --right;
            if (right < right_end) {
                break;
            }
        }
    }

    // Dump the remainder of the first list into the merged list.
    while (left >= left_end) {
        *list_back = *left;
        --list_back;
        --left;
    }

    // Dump the remainder of the second list into the merged list.
    while (right >= right_end) {
        *list_back = *right;
        --list_back;
        --right;
    }
}

/**
 * Merge two lists from the origin to the buffer.
 *
 * @see merge(RandAccessIterator, typename std::iterator_traits<RandAccessIterator>::value_type *, typename std::iterator_traits<RandAccessIterator>::difference_type, typename std::iterator_traits<RandAccessIterator>::difference_type, bool, bool)
 */
template<class RandAccessIterator>
void mergeListList(
    RandAccessIterator front,
    typename std::iterator_traits<RandAccessIterator>::value_type * buffer,
    typename std::iterator_traits<RandAccessIterator>::difference_type middle,
    typename std::iterator_traits<RandAccessIterator>::difference_type length
) {
    auto left = front;
    auto left_end = front + middle;
    auto right = left_end;
    auto right_end = front + length;

    // Merge the lists until one list is completely processed.
    while (true) {
        if (*left < *right) {
            *buffer = *left;
            ++buffer;
            ++left;
            if (left >= left_end) {
                break;
            }
        } else {
            *buffer = *right;
            ++buffer;
            ++right;
            if (right >= right_end) {
                break;
            }
        }
    }

    // Dump the remainder of the first list into the merged list.
    while (left < left_end) {
        *buffer = *left;
        ++buffer;
        ++left;
    }

    // Dump the remainder of the second list into the merged list.
    while (right < right_end) {
        *buffer = *right;
        ++buffer;
        ++right;
    }
}

/**
 * Merge two sorted lists into one sorted list.
 *
 * The lists may reside in the origin, the buffer, or both. The buffer is a
 * temporary space which mirrors the origin. The lists must be "adjacent". If
 * one list is in the origin and the other is in the buffer, they must be
 * adjacent when one is transferred to its analogous position.
 *
 * @param front An iterator at the front of the origin.
 * @param buffer A pointer to the front of the buffer.
 * @param middle The length of the first list.
 * @param length The total length of the two lists.
 * @param left_in_buffer Whether the first list is in the buffer.
 * @param right_in_buffer Whether the second list is in the buffer.
 * @return Whether the merged list is in the buffer.
 */
template<class RandAccessIterator>
bool merge(
    RandAccessIterator front,
    typename std::iterator_traits<RandAccessIterator>::value_type * buffer,
    typename std::iterator_traits<RandAccessIterator>::difference_type middle,
    typename std::iterator_traits<RandAccessIterator>::difference_type length,
    bool left_in_buffer,
    bool right_in_buffer
) {
    if (left_in_buffer) {
        if (right_in_buffer) {
            mergeBufferBuffer(front, buffer, middle, length);
        } else {
            mergeBufferList(front, buffer, middle, length);
        }
    } else {
        if (right_in_buffer) {
            mergeListBuffer(front, buffer, middle, length);
        } else {
            mergeListList(front, buffer, middle, length);
            return true;
        }
    }
    return false;
}

/**
 * Helper function for performing merge sort.
 *
 * @param front An iterator to the front of the list.
 * @param buffer A pointer to the front of the buffer.
 * @param length The list length.
 * @return Whether the sorted list is in the buffer.
 */
template<class RandAccessIterator>
bool _mergeSort(
    RandAccessIterator front,
    typename std::iterator_traits<RandAccessIterator>::value_type * buffer,
    typename std::iterator_traits<RandAccessIterator>::difference_type length
) {
    // Use a simpler sorting algorithm for the last part to improve speed.
    if (length <= 5) {
        insertionSort(front, front + length);
        return false;
    }

    const auto left_length = length / 2;
    const bool left_in_buffer = _mergeSort(front, buffer, left_length);
    const bool right_in_buffer = _mergeSort(
        front + left_length, buffer + left_length, length - left_length
    );
    const bool in_buffer = merge(
        front, buffer, left_length, length, left_in_buffer, right_in_buffer
    );

    return in_buffer;
}

} // namespace

/**
 * Perform merge sort on an int array.
 *
 * This function is written for clarity and is not optimized.
 *
 * @param array Pointer to the front of the array.
 * @param length The array length.
 */
void mergeSort(int * array, const unsigned long length) {
    if (length <= 1) {
        return;
    }

    const unsigned long middle = length / 2;
    mergeSort(array, middle);
    mergeSort(array + middle, length - middle);
    merge(array, middle, length);
}

/**
 * Perform merge sort on a list.
 *
 * @param front A random access iterator to the front of the list.
 * @param back A random access iterator to the back of the list.
 */
template<class RandAccessIterator>
void mergeSort(RandAccessIterator front, RandAccessIterator back) {
    using value_type =
            typename std::iterator_traits<RandAccessIterator>::value_type;

    auto length = back - front;
    auto buffer = new value_type[back - front];

    const bool in_buffer = _mergeSort(front, buffer, back - front);

    // Copy results from the buffer if it is there instead of the origin.
    if (in_buffer) {
        for (int i = 0; i < length; ++i) {
            front[i] = buffer[i];
        }
    }

    delete[] buffer;
}
