# Merge Sort
Merge sort is my favorite sorting algorithm (I know it sounds weird to have a favorite sorting algorithm). It's an elegant divide and conquer algorithm with a time complexity of Θ(n log(n)). That’s big theta, not big O. Almost all the work is done in the merging step, which makes it the most important part to understand. Without proper merging, you end up with a [half-hearted merge sort](https://xkcd.com/1185/).

## Python
The Python implementation is written for simplicity and is hopefully easy to understand. Notice how much longer the merging part is compared to the recursive function.

This code runs very slowly, about 15 times slower than Python’s build-in sorting function.

## C++
There are two implementations. One sorts an `int` array and is written for simplicity. The other implementation is closer to what "good" code looks like. It is more flexible and runs faster.

### Performance
Merging two lists is often done by creating a new list. In-place merge sort is possible, but is apparently not very fast.

To speed things up, we can allocate a big buffer in advance and use it as our workspace. The merge function can simply merge two lists into the buffer and copy the result back. Copying the result every time is not ideal. What we can do instead is leave the results where they are and keep track of them. The hardest part, which isn’t really that hard, is merging lists which could either be in the original location or the buffer. If both lists are in the same location, we can just merge them into the alternate location. If the left list is in the buffer and the right list isn’t, we can always merge into the original location without overwriting unmerged parts of the right list. If the left list is in the original location and the right list isn’t, we can merge backwards into the original location to avoid overwriting unmerged parts of the left list. In three of the four cases, the result ends up in the original location. If by chance the final result remains in the buffer, we simply copy it back to the original location. This implementation takes about 50% more time than a highly optimized implementation of `std::sort()`.

50% longer is not bad considering that `std::sort()` is not restricted to using merge sort. We can improve on this by “cheating” a bit. Once we recurse down to a small list, it’s better to use a simpler sorting algorithm. The final implementation switches over to insertion sort for lists of size 5 or smaller. This small change brings the difference down to about 30%.
