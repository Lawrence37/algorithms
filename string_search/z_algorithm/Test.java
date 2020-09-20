package algorithms.string_search.z_algorithm;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;

import algorithms.TestUtils;
import algorithms.string_search.z_algorithm.ZAlgorithm;


public class Test {
    public static void main(String[] args) {
        testCorrectnessZ();
        testCorrectnessSearch1();
        testCorrectnessSearch2();
        testCorrectnessSearch3();
        warmUp();
        testSpeedZ();
        testSpeedSearch1();
        testSpeedSearch2();
    }

    /**
     * Creates a new string, which is the provided string repeated.
     *
     * This is a simple stand-in for String.repeat(int) introduced in Java 11.
     *
     * @param s The string to repeat.
     * @param repetitions The number of repetitions.
     * @return The new string.
     */
    private static String repeatString(String s, int repetitions) {
        StringBuilder builder = new StringBuilder();
        for (int i = 0; i < repetitions; i++) {
            builder.append(s);
        }
        return builder.toString();
    }

    /**
     * Performs a brute force string search.
     *
     * Matches are found by iterating through the string and using
     * {@link String.indexOf(String, int)}.
     */
    private static List<Integer> searchBrute(String string, String pattern) {
        ArrayList<Integer> indices = new ArrayList<>();
        int index = -1;

        do {
            index = string.indexOf(pattern, index + 1);
            indices.add(index);
        } while (index >= 0);
        indices.remove(indices.size() - 1);

        return indices;
    }

    private static void testCorrectnessSearch1() {
        // A 13-character string is repeated here. The pattern matches the 0th
        // and 4th indices of the base string. Thus, every 13th index starting
        // from 0 and 4 should match.
        final int REPETITIONS = 50;
        String s = repeatString("012301230123-", REPETITIONS);
        String pattern = "01230123";
        List<Integer> indices = ZAlgorithm.indicesOf(s, pattern);

        assert indices.size() == 2 * REPETITIONS;
        for (int i = 0; i < REPETITIONS; i++) {
            assert indices.contains(i * 13);
            assert indices.contains(i * 13 + 4);
        }
    }

    private static void testCorrectnessSearch2() {
        final int REPETITIONS = 20;
        String s = repeatString("*", REPETITIONS);
        String pattern = "*";
        List<Integer> indices = ZAlgorithm.indicesOf(s, pattern);

        assert indices.size() == REPETITIONS;
        assert (new HashSet<Integer>(indices)).size() == REPETITIONS;
    }

    private static void testCorrectnessSearch3() {
        String s = "123412341234";
        String pattern = "12341234";
        List<Integer> indices = ZAlgorithm.indicesOf(s, pattern);

        assert indices.size() == 2;
        assert indices.contains(0);
        assert indices.contains(4);
    }

    private static void testCorrectnessZ() {
        String s = "01201001201210";
        int[] expected = {14, 0, 0, 2, 0, 1, 5, 0, 0, 3, 0, 0, 0, 1};
        int[] actual = ZAlgorithm.zArray(s);

        assert expected.length == actual.length;
        for (int i = 0; i < expected.length; i++) {
            assert expected[i] == actual[i];
        }
    }

    private static void testSpeedSearch1() {
        System.out.println("\nSimple Search Speed");
        System.out.println("        n  Z Algorithm  Brute Force");

        for (int n : new int[]{10000, 100000, 1000000, 10000000, 100000000}) {
            String s = repeatString("012012012-", n / 10);
            String pattern = "012012";
            double timeZ = TestUtils.time(
                () -> ZAlgorithm.indicesOf(s, pattern)
            );
            double timeBrute = TestUtils.time(
                () -> searchBrute(s, pattern)
            );
            System.out.println(
                String.format("%9d  %11f  %11f", n, timeZ, timeBrute)
            );
        }
    }

    private static void testSpeedSearch2() {
        System.out.println("\nLong String Search Speed");
        System.out.println("(n is string length, m is pattern length)");
        System.out.println("     n       m  Z Algorithm  Brute Force");

        for (int n : new int[]{100, 1000, 10000, 100000}) {
            final int m = n / 10;
            String s = repeatString("**********", n / 10);
            String pattern = repeatString("**********", m / 10);
            double timeZ = TestUtils.time(
                () -> ZAlgorithm.indicesOf(s, pattern)
            );
            double timeBrute = TestUtils.time(
                () -> searchBrute(s, pattern)
            );
            System.out.println(
                String.format("%6d  %6d  %11f  %11f", n, m, timeZ, timeBrute)
            );
        }
    }

    private static void testSpeedZ() {
        System.out.println("\nZ Array Creation Speed");
        System.out.println("        n  Seconds");

        for (int n : new int[]{10000, 100000, 1000000, 10000000, 100000000}) {
            String s = repeatString("*", n);
            double time = TestUtils.time(() -> ZAlgorithm.zArray(s));
            System.out.println(String.format("%9d  %f", n, time));
        }
    }

    private static void warmUp() {
        int[] j = new int[1000];
        for (int i = 0; i < 1000000000; i++) {
            j[i % 100] = i;
        }
    }
}
