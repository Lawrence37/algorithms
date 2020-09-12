package algorithms;

import java.util.function.Supplier;


public class TestUtils {
    /** Runs the provided function and returns the runtime in seconds. */
    public static <T> double time(Supplier<T> function) {
        long start = System.nanoTime();
        function.get();
        long end = System.nanoTime();
        return (end - start) / 1000000000.0;
    }
}
