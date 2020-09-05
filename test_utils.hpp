#pragma once

#include <chrono>
#include <functional>


/**
 * Time the execution of a function.
 *
 * The provided function is executed, and the execution time is recorded. Note
 * that this measures the elapsed time and may potentially be significantly
 * longer than the actual CPU time used.
 *
 * @param function The parameter-free function to run. It may be more convenient
 * to encapsulate a code block in a lambda and time the lambda instead.
 * @return The execution time, in seconds.
 */
double time(std::function<void()> function) {
    auto start_time = std::chrono::high_resolution_clock::now();
    function();
    auto end_time = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::duration<double>>(
            end_time - start_time).count();
}
