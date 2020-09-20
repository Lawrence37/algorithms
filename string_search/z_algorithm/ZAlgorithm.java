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

        if (
            string == null
            || pattern == null
            || string.length() < pattern.length()
        ) {
            return indices;
        }

        String superString = pattern + "\0" + string;
        final int stringIndex = pattern.length() + 1;
        // Don't search the last pattern.length() - 1 characters because the
        // pattern doesn't even fit.
        final int maxIndex = superString.length() - pattern.length();
        final int patternZsNeeded = Math.min(
            pattern.length(), string.length() - pattern.length() + 1
        );
        int[] zs = new int[maxIndex + 1];

        // We could calculate all the Z values, but some are not needed.
        zArray(superString, zs, 0, patternZsNeeded);
        zArray(superString, zs, stringIndex, maxIndex + 1);

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
        if (s == null) {
            return new int[0];
        }

        int[] array = new int[s.length()];
        zArray(s, array, 0, s.length());
        return array;
    }

    /**
     * Calculates the Z array for the given string.
     *
     * This method allows for calculation of a section of the Z array. Z values
     * to the left of the section must be pre-calculated or known to be unused
     * by this method.
     *
     * @param s The string.
     * @param array The array to store the Z values in.
     * @param startIndex The index of the left-most Z value to calculate.
     * @param endIndex The index after the right-most Z value to calculate.
     */
    private static void zArray(
        String s, int[] array, int startIndex, int endIndex
    ) {
        final int length =
            Math.min(Math.min(s.length(), array.length), endIndex);

        if (length <= startIndex) {
            // Nothing to do.
            return;
        }

        int unexploredIndex = startIndex;
        int bestZIndex = -1;

        if (startIndex == 0) {
            // The first Z value is always the string length.
            array[0] = s.length();
            unexploredIndex = 1;
        }

        for (int index = unexploredIndex; index < length; index++) {
            if (index >= unexploredIndex) {
                // Time to explore new characters.
                array[index] = matchLength(s, index);
                bestZIndex = index;
                unexploredIndex = index + array[index];
            } else {
                int exploredRemaining = unexploredIndex - index;
                int subIndex = index - bestZIndex;

                if (array[subIndex] < exploredRemaining) {
                    // We've seen this pattern before.
                    array[index] = array[subIndex];
                } else if (array[subIndex] > exploredRemaining) {
                    // This is part of a pattern we've seen before.
                    array[index] = exploredRemaining;
                } else {
                    // We've seen this pattern, and possibly more.
                    array[index] = matchLength(s, index, exploredRemaining);
                    bestZIndex = index;
                    unexploredIndex = index + array[index];
                }
            }
        }
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
