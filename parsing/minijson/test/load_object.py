'''
Tests for loading objects from JSON
'''

import pytest
from .. import minijson


def _assert_dict(obj, size: int = None):
    assert isinstance(obj, dict)
    if size is not None:
        assert len(obj) == size


def test_empty():
    json = '{}'
    result = minijson.load(json)
    _assert_dict(result, 0)


def test_1():
    json = '{"key": "value"}'
    result = minijson.load(json)
    _assert_dict(result, 1)
    assert 'key' in result
    assert result['key'] == 'value'


def test_2():
    json = '{"key1": "value1", "key2": "value2"}'
    result = minijson.load(json)
    _assert_dict(result, 2)
    assert 'key1' in result
    assert 'key2' in result
    assert result['key1'] == 'value1'
    assert result['key2'] == 'value2'


def test_lists():
    json = '{"list": [], "string": "hello"}'
    result = minijson.load(json)
    _assert_dict(result, 2)
    assert 'list' in result
    assert 'string' in result
    assert isinstance(result['list'], list)
    assert len(result['list']) == 0
    assert result['string'] == 'hello'


def test_whitespace_1():
    json = '  {  }  '
    result = minijson.load(json)
    _assert_dict(result, 0)


def test_whitespace_2():
    json = '{\n}'
    result = minijson.load(json)
    _assert_dict(result, 0)


def test_whitespace_3():
    json = '  {  "key"  :  "value"  }  '
    result = minijson.load(json)
    _assert_dict(result, 1)
    assert 'key' in result
    assert result['key'] == 'value'


def test_unmatched_brace_1():
    json = '{"key": "value"'
    with pytest.raises(ValueError):
        minijson.load(json)


def test_unmatched_brace_2():
    json = '"key": "value"}'
    with pytest.raises(ValueError):
        minijson.load(json)


def test_leading_comma():
    json = '{, "key": "value"}'
    with pytest.raises(ValueError):
        minijson.load(json)


def test_trailing_comma():
    json = '{"key": "value", }'
    with pytest.raises(ValueError):
        minijson.load(json)


def test_double_comma():
    json = '{"key1": "value1", , "key2": "value2"}'
    with pytest.raises(ValueError):
        minijson.load(json)


def test_no_comma():
    json = '{"key1": "value1" "key2": "value2"}'
    with pytest.raises(ValueError):
        minijson.load(json)


def test_unhashable_key():
    json = '{[]: "value"}'
    with pytest.raises(ValueError):
        minijson.load(json)
