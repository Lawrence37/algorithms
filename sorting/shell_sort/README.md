# Shell Sort
How do you make something run faster? Do it over and over again. Shell sort improves on insertion sort by performing insertion sort multiple times. The key insight is that insertion sort is slow because inserting an item may require many elements to be shifted over by one. Wouldn't it be nice if we could shift them over large distances in one operation?

Shell sort achieves this by performing insertion sort on sub-lists made from every kth element. Now, we shift elements by a distance of k instead of one! Begin with a k comparable to the size of the list. For every possible sub-list with a gap size of k, perform insertion sort. Repeat for progressively smaller values of k until k is one.

What gap sizes should be used? There are many gap size schemes. Some make Shell sort worse than insertion sort. Good schemes reduce the time complexity. Most gap sequences change exponentially.

## C++
The C++ implementation hides the insertion sort component, allowing you to see the heart of Shell sort. This is possible thanks to skip iterators, which allow a standard insertion sort function to sort a sub-list with a specified gap size.

The gap sizes used here are from Sedgewick. It leads to a time complexity of O(n^(4/3)) and an average of O(n^(7/6)).
