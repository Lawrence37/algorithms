'''
Tests for loading lists from JSON
'''

import pytest
from .. import minijson


def _assert_list(obj, size: int = None):
    assert isinstance(obj, list)
    if size is not None:
        assert len(obj) == size


def test_empty():
    json = '[]'
    result = minijson.load(json)
    _assert_list(result, 0)


def test_str_1():
    json = '["hello"]'
    result = minijson.load(json)
    _assert_list(result, 1)
    assert result[0] == 'hello'


def test_str_2():
    json = '["hello", "world"]'
    result = minijson.load(json)
    _assert_list(result, 2)
    assert result[0] == 'hello'
    assert result[1] == 'world'


def test_num_1():
    json = '[0]'
    result = minijson.load(json)
    _assert_list(result, 1)
    assert result[0] == 0


def test_num_2():
    json = '[0, 1.0]'
    result = minijson.load(json)
    _assert_list(result, 2)
    assert result[0] == 0
    assert result[1] == 1.0


def test_bad_num():
    json = '[0, .]'
    with pytest.raises(ValueError):
        minijson.load(json)


def test_objects():
    json = '[{}, {}]'
    result = minijson.load(json)
    _assert_list(result, 2)
    assert isinstance(result[0], dict)
    assert isinstance(result[1], dict)
    assert len(result[0]) == 0
    assert len(result[1]) == 0


def test_whitespace_1():
    json = '  [ ]  '
    result = minijson.load(json)
    _assert_list(result, 0)


def test_whitespace_2():
    json = '[\n]'
    result = minijson.load(json)
    _assert_list(result, 0)


def test_whitespace_3():
    json = '  [ "hello" ]  '
    result = minijson.load(json)
    _assert_list(result, 1)
    assert result[0] == 'hello'


def test_unmatched_bracket_1():
    json = '["hello"'
    with pytest.raises(ValueError):
        minijson.load(json)


def test_unmatched_bracket_2():
    json = '"hello"]'
    with pytest.raises(ValueError):
        minijson.load(json)


def test_unmatched_quote():
    json = '["hello]'
    with pytest.raises(ValueError):
        minijson.load(json)


def test_no_comma():
    json = '["hello" "world"]'
    with pytest.raises(ValueError):
        minijson.load(json)


def test_double_comma():
    json = '["hello", , "world"]'
    with pytest.raises(ValueError):
        minijson.load(json)


def test_leading_comma():
    json = '[,"hello", "world"]'
    with pytest.raises(ValueError):
        minijson.load(json)


def test_trailing_comma():
    json = '["hello", "world",]'
    with pytest.raises(ValueError):
        minijson.load(json)
