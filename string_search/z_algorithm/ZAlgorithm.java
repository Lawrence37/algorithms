package algorithms.string_search.z_algorithm;

import java.util.ArrayList;
import java.util.List;


public class ZAlgorithm {
    /**
     * Finds all indices of a string where the pattern matches a substring.
     *
     * This uses the Z algorithm to locate all occurrences. The string and
     * pattern must not contain the null character ("\0").
     *
     * @param string The string to search.
     * @param pattern The string to find.
     * @return A list of all indices.
     */
    public static List<Integer> indicesOf(String string, String pattern) {
        List<Integer> indices = new ArrayList<>();
        String superString = pattern + "\0" + string;
        final int stringIndex = pattern.length() + 1;
        // Don't search the last pattern.length() - 1 characters because the
        // pattern doesn't even fit.
        final int maxIndex = superString.length() - pattern.length();
        final int[] zs = zArray(superString, maxIndex + 1);

        // Look for matches.
        for (int i = stringIndex; i <= maxIndex; i++) {
            if (zs[i] == pattern.length()) {
                indices.add(i - stringIndex);
            }
        }

        return indices;
    }

    /** Calculates and returns the Z array for the given string. */
    public static int[] zArray(String s) {
        return zArray(s, s.length());
    }

    /**
     * Calculates the Z array for the given string.
     *
     * @param s The string.
     * @param maxLength The maximum number of Z values to calculate. The values
     * are calculated from left to right.
     * @return The Z array.
     */
    public static int[] zArray(String s, int maxLength) {
        final int length = Math.min(maxLength, s.length());
        int[] zArray = new int[length];

        if (length == 0) {
            // Nothing to do.
            return zArray;
        }

        // The first Z value is always the string length.
        zArray[0] = s.length();

        int unexploredIndex = 1;
        int bestZIndex = 0;

        for (int index = 1; index < length; index++) {
            if (index >= unexploredIndex) {
                // Time to explore new characters.
                zArray[index] = matchLength(s, index);
                bestZIndex = index;
                unexploredIndex = index + zArray[index];
            } else {
                int exploredRemaining = unexploredIndex - index;
                int subIndex = index - bestZIndex;

                if (zArray[subIndex] < exploredRemaining) {
                    // We've seen this pattern before.
                    zArray[index] = zArray[subIndex];
                } else if (zArray[subIndex] > exploredRemaining) {
                    // This is part of a pattern we've seen before.
                    zArray[index] = exploredRemaining;
                } else {
                    // We've seen this pattern, and possibly more.
                    zArray[index] = matchLength(s, index, exploredRemaining);
                    bestZIndex = index;
                    unexploredIndex = index + zArray[index];
                }
            }
        }

        return zArray;
    }

    /**
     * Find the length of the longest prefix of a given suffix which matches
     * with a prefix of the given string.
     *
     * @param s The string.
     * @param start The index at which the suffix starts.
     * @return The length of the longest match.
     */
    private static int matchLength(String s, int start) {
        return matchLength(s, start, 0);
    }

    /**
     * Find the length of the longest prefix of a given suffix which matches
     * with a prefix of the given string.
     *
     * This is a special optimization of {@link matchLength(String, int)} used
     * when it is known that some characters match. Such characters are assumed
     * to match to save computation time.
     *
     * @param s The string.
     * @param start The index at which the suffix starts.
     * @param known The known minimum length of the match.
     * @return The length of the longest match.
     */
    private static int matchLength(String s, int start, int known) {
        final int maxLength = s.length() - start;
        int length;

        for (
            length = known;
            length < maxLength && s.charAt(length) == s.charAt(start + length);
            length++
        );

        return length;
    }
}
