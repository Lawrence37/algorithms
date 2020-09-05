'''
Tests for merge sort.
'''


from timeit import timeit

from .. import test_utils
from .merge_sort import merge_sort


unsorted = test_utils.random_int_list(1000)

# Test correctness.
assert not test_utils.is_sorted(unsorted)
sorted_list = merge_sort(unsorted)
assert test_utils.is_sorted(sorted_list)

# Inspect time complexity.
for i in range(10000000):
    pass  # "Warm up" the CPU.
print('      n\tmerge_sort()\tsorted()')
for length in [10, 100, 1000, 10000, 100000, 1000000]:
    unsorted = test_utils.random_int_list(length)
    unsorted_copy = unsorted[:]

    merge_sort_time = timeit(lambda: merge_sort(unsorted), number=1)
    sorted_time = timeit(lambda: sorted(unsorted_copy), number=1)
    print(f'{length:7}\t{merge_sort_time:.8f}\t{sorted_time:.8f}')
