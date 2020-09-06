from random import shuffle

from ..test_utils import is_sorted


def bogosort(l: list):
    '''
    Performs bogosort on the list.
    '''
    while not is_sorted(l):
        shuffle(l)
