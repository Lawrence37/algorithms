# Algorithms
This repository is intended to be a small collection of common algorithms for educational and demonstration purposes. Implementations exist in several programing languages. Some implementations are meant to be simple and easy to read while others are optimized for performance.

## Tests
There are tests for algorithm correctness and performance.

### C++
Tests for C++ algorithms can be run by compiling the test source code and running the resulting executable. Optimization flags are recommended for performance tests to best represent production software. Debug flags may be used to inspect how implementations work.
```shell
cd sorting/merge_sort
g++ test.cpp -o test.out -O2
./test.out
```

### Python 3
Python tests can be run from the repository’s root directory. Run the tests as modules with the `-m` flag.
```shell
python -m sorting.merge_sort.test
```
