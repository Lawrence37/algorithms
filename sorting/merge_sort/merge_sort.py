'''
A simple demonstration of the merge sort algorithm.
'''


def merge_sort(unsorted):
    '''
    Performs a simple merge sort on a list and returns the results in a new
    list.
    '''
    # Base case.
    if len(unsorted) <= 1:
        return unsorted

    # Recurse on both halves and merge the results.
    middle = int(len(unsorted) / 2)
    sorted = merge(
        merge_sort(unsorted[:middle]),
        merge_sort(unsorted[middle:])
    )

    return sorted


def merge(left, right):
    '''
    Merge the sorted lists ``left`` and ``right`` and return the results in a
    new list.
    '''
    merged = []
    l_iter = iter(left)
    r_iter = iter(right)

    # Start merging the lists until one list is completely used.
    l_val = next(l_iter)
    r_val = next(r_iter)
    while l_val is not None and r_val is not None:
        if l_val < r_val:
            # Left list has the lowest value.
            merged.append(l_val)
            l_val = next(l_iter, None)
        else:
            # Right list has the lowest value.
            merged.append(r_val)
            r_val = next(r_iter, None)

    if l_val is not None:
        # If the left list isn't completely used, dump the remaining values.
        while l_val is not None:
            merged.append(l_val)
            l_val = next(l_iter, None)

    if r_val is not None:
        # If the right list isn't completely used, dump the remaining values.
        while r_val is not None:
            merged.append(r_val)
            r_val = next(r_iter, None)

    return merged
