# Z Algorithm
The Z algorithm is not a string search algorithm by itself. It is used to construct an array of Z values for a given string. Designing a string search algorithm using the Z algorithm is very simple.

## Z Value Definition
For a string S of size n, the Z value at index `i` is the length of the longest prefix of S which matches a prefix of the suffix of S beginning at index `i`. If that’s not confusing, I challenge you to explain the epsilon-delta definition of a limit.

An example should be easier to understand. Start with a string S:

```
S = “programming problem”
```

The string is 19 characters long, so there are 19 Z values. Let’s choose index 12. The suffix of S beginning at index 12 is `“problem”`. Now, line up the suffix with the original string:

```
programming problem
problem
```

Start from the left and see how many characters match. Once the characters are different, stop. How many characters matched? In this example, it’s 3. They both start with `“pro”`. The fourth letters don’t match, so we stop.

The Z value at index 12 is 3.

## String Search
Let’s say you want to find the string P in the string S. Create a new string which is the concatenation of P, a unique character, and S. Use the Z algorithm to find the Z values of this new string. If there are any occurrences of P in S, there will be one or more Z values equal to the length of P. The Z values will be located where the occurrences begin.

### Example
```
P = “no”
S = “no, not again”
```

First, create the new string with a unique character.

```
“no☺no, not again”
```

Find all the Z values.

```
[16, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1]
  n  o  ☺  n  o  ,  ␣  n  o  t  ␣  a  g  a  i  n
```

Look for Z values equal to 2.

## Implementation
The Z array can be computed in linear time. The basic idea is to work from left to right and use previous results to avoid unnecessary computation.

The first Z value is always equal to the length of the string. It tells us nothing useful, and is usually ignored. The real work begins at the second index (`i = 1`). Since there is no useful information yet, the best we can do is calculate the Z value directly and move on to the next index. In doing so, we may explore parts of the string beyond index `i`. A good idea here is to keep track of which parts are unexplored. (In this document, the mismatched character found during direct calculation of the Z value is considered “unexplored”.) It is a reminder to not linger in the explored parts, otherwise we may end up with a non-linear runtime. You will also want to associate the current index with the unexplored region. The reason will become clear later.

Now, there are two possible cases. We could be in the unexplored region. We don’t know anything about what’s next, so the only thing to do is to directly calculate the Z value. The second case is more interesting. The explored region matches an earlier part of the string. Remember the index associated with the unexplored region? The substring starting at that index and ending right before the unexplored region matches the first part of the string. If we are `j` characters into the substring, we can use the `j`th Z value to help us. We just need to compare the `j`th Z value to the number of characters remaining in the substring. There are three cases here.

The first case is when the `j`th Z value is less than the remaining explored characters. Think about what would happen if you calculated the `j`th Z value directly. If the Z value was 2, you would have seen two matches and stopped after the 3rd character because they didn’t match. Since the number of remaining explored characters in this case is at least 3, the three characters starting at index `j` are exactly the same as those at index `i`. Directly calculating the Z value at index `i` would look exactly the same as doing it at index `j`! Therefore, both Z values are the same.

The second case is when the `j`th Z value is greater than the remaining explored characters. From before, we know the explored characters match with a previous substring. The next thing you should know is that the substrings stop matching immediately once you go into the unexplored region. Why? If they matched, your direct calculation of the Z value would have continued into the unexplored region. If you perform direct calculation for index `i`, everything would look the same as in the calculation for `j` until you hit the unexplored region. For `j`, you continued. Therefore, for `i`, you stop. The Z value is the remaining explored characters.

The final case is when the `j`th Z value is equal to the remaining explored characters. Both substrings stopped matching the prefix at the same point. Their next characters could either be the same or different. They just can’t match the prefix. For example, the prefix could be `“abcabcd”`, the substring at `j` is `“abc…”`, and the substring at `i` is `“abc…”`. The next character for the substrings can be anything except for `“a”`. Since we don’t know, we must directly compute the Z value.

## Optimization
From the previous paragraph, you may notice that direct computation performs repeated work. It is known that the explored region matches. We can simply skip the comparison of the explored characters. With this optimization, the algorithm has a linear time complexity.

In string search, there is no use in searching at the very end where the pattern doesn’t even fit. Calculating the Z values there is not needed. In the extreme, the pattern is longer than the string. There can never be a match.

The previous optimization leads to another one which works under some conditions. Suppose P and S are of length n. For the Z values corresponding to S, only the first one needs to be calculated. A consequence is that the last n - 1 Z values corresponding to P are never used! The `j` index will never exceed zero. What if S is one character longer? Only the first two Z values corresponding to S are needed. The `j` index will never exceed one. There is room for optimization as long as `j` is guaranteed to be less than n - 1. Since the maximum possible value of `j` is the length of S minus the length of P, the length of S must be less than twice the length of P minus 1.
