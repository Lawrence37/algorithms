'''
Tests for bogosort.
'''


from timeit import timeit

from .. import test_utils
from .bogosort import bogosort


unsorted = test_utils.random_int_list(5)

# Test correctness.
assert not test_utils.is_sorted(unsorted)
bogosort(unsorted)
assert test_utils.is_sorted(unsorted)

# Inspect time complexity.
for i in range(10000000):
    pass  # "Warm up" the CPU.
print('  n\tbogosort()\tsorted()')
for length in [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]:
    unsorted = test_utils.random_int_list(length)
    unsorted_copy = unsorted[:]

    bogosort_time = timeit(lambda: bogosort(unsorted), number=1)
    sorted_time = timeit(lambda: sorted(unsorted_copy), number=1)
    print(f'{length:3}\t{bogosort_time:.8f}\t{sorted_time:.8f}')
