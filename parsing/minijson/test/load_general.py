'''
Miscellaneous tests for loading of JSON.
'''

import pytest
from .. import minijson


def test_empty_1():
    json = ''
    result = minijson.load(json)
    assert result is None


def test_empty_2():
    json = ' \n\t '
    result = minijson.load(json)
    assert result is None


def test_double_list():
    json = ' [] [] '
    with pytest.raises(ValueError):
        minijson.load(json)


def test_double_object():
    json = ' {} {} '
    with pytest.raises(ValueError):
        minijson.load(json)
