from random import randint
from typing import List


def is_sorted(target: list) -> bool:
    '''
    Checks if the target list is sorted in ascending order.
    '''
    for i in range(len(target) - 1):
        if target[i] > target[i + 1]:
            return False
    return True


def random_int_list(
    length: int, min_value: int = -1000, max_value: int = 1000
) -> List[int]:
    '''
    Create a list of random integers.
    '''
    return [randint(min_value, max_value) for i in range(length)]
