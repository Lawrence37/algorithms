# minijson
A small library for parsing basic JSON. Supports objects, lists, numbers, and simple strings.

## Principles
minijson works like a one-pass compiler. The JSON language is defined by a grammar which, for example, can be represented in EBNF. minijson parses from the top down using the grammar as a guide. This leads to a clean source code structure in which each grammar element is handled by individual functions.

To maintain efficiency, minijson refrains from excessive string manipulation. String operations can be expensive for multiple reasons. Strings are immutable objects, so any modifications actually involve the creation of new strings. An efficient way to build a new string is to manipulate a list of individual characters and join them when finished. Referring to part of a string can also be expensive. Using Python slices creates copies. It is more efficient to use indices which refer to the start and end of a substring.

## Usage
```python3
from minijson import load
message = load('["Hello", "world!"]')
print(' '.join(message))  # Hello world!
```

## Tests
Tests use [pytest](https://docs.pytest.org/en/stable/). To run all tests,
```bash
pytest test/*
```
