class _Cursor:
    '''
    A cursor within a string.
    '''

    def __init__(self, string: str, index: int):
        '''
        Creates a cursor for the string ``string`` at index ``index``.
        '''
        self.string = list(string)
        self._index = index

    @property
    def index(self) -> int:
        return self._index

    def is_end(self) -> bool:
        return self._index == len(self.string)

    def next(self) -> str:
        '''
        Returns the next character and advances the cursor.
        '''
        char = self.peek()
        if char is not None:
            self._index += 1
        return char

    def peek(self) -> str:
        '''
        Returns the next character without affecting the cursor.
        '''
        if self.is_end():
            return None
        return self.string[self.index]


def _assert_not_end(stream: _Cursor):
    '''
    Raises a ``ValueError`` if the cursor has reached the end.
    '''
    if stream.peek() is None:
        raise ValueError('Unexpectedly reached end of string')


def _raise_unexpected_token(stream: _Cursor):
    '''
    Raises a ``ValueError`` with a message indicating an unexpected token at
    the current cursor position.
    '''
    raise ValueError(
        f'Unexpected token {stream.peek()} at index {stream.index}'
    )


def _skip_ws(stream: _Cursor):
    '''
    Advances the cursor until the next character is not whitespace.
    '''
    while stream.peek() is not None and stream.peek() in ' \t\n':
        stream.next()


def _string(stream: _Cursor) -> str:
    '''
    Parses and returns a JSON string.
    '''
    # A string of characters, excluding double quotes, enclosed by double
    # quotes.
    assert stream.next() == '"'
    string = []
    while True:
        _assert_not_end(stream)
        char = stream.next()
        if char == '"':
            break
        string.append(char)
    return ''.join(string)


def _number(stream: _Cursor):
    '''
    Parses and returns a JSON number.
    '''
    # A string of digits and up to one decimal character.
    start = stream.index
    decimal = False
    char = stream.peek()
    while (
        char is not None
        and (char.isdigit() or (not decimal and char == '.'))
    ):
        decimal = decimal or char == '.'
        stream.next()
        char = stream.peek()
    if decimal and start + 1 == stream.index:
        _raise_unexpected_token(stream)
    number_str = ''.join(stream.string[start:stream.index])
    if decimal:
        return float(number_str)
    return int(number_str)


def _expr(stream: _Cursor):
    '''
    Parses and returns a JSON expression.
    '''
    # A string, number, list, or object.
    _assert_not_end(stream)
    char = stream.peek()
    if char == '"':
        result = _string(stream)
        return result
    if char.isdigit() or char == '.':
        result = _number(stream)
        return result
    if char == '[':
        result = _list(stream)
        return result
    if char == '{':
        result = _object(stream)
        return result
    _raise_unexpected_token(stream)


def _list(stream: _Cursor) -> list:
    '''
    Parses and returns a JSON list.
    '''
    # A left bracket, followed by a string of comma-separated expressions with
    # optional whitespace around items, followed by a right bracket.
    assert stream.next() == '['
    result = []
    _skip_ws(stream)
    _assert_not_end(stream)
    if stream.peek() == ',':
        _raise_unexpected_token(stream)
    while stream.peek() != ']':
        if len(result) > 0:
            if stream.peek() != ',':
                _raise_unexpected_token(stream)
            stream.next()
            _skip_ws(stream)
        expr = _expr(stream)
        result.append(expr)
        _skip_ws(stream)
        _assert_not_end(stream)
    stream.next()
    return result


def _key(stream: _Cursor):
    '''
    Parses and returns a JSON object key/field.
    '''
    # An expression, excluding objects and lists.
    _assert_not_end(stream)
    char = stream.peek()
    if char in '[{':
        _raise_unexpected_token(stream)
    return _expr(stream)


def _value(stream: _Cursor):
    '''
    Parses and returns a JSON object value.
    '''
    # An expression.
    return _expr(stream)


def _key_value(stream: _Cursor):
    '''
    Parses and returns a JSON object key-value pair.
    '''
    # A key, optional whitespace, colon, optional whitespace, and value.
    key = _key(stream)
    _skip_ws(stream)
    _assert_not_end(stream)
    if stream.peek() != ':':
        raise ValueError(
            f'Expected ":" before token {stream.peek()} at index '
            f'{stream.index}'
        )
    stream.next()
    _skip_ws(stream)
    _assert_not_end(stream)
    value = _value(stream)
    return key, value


def _object(stream: _Cursor):
    '''
    Parses and returns a JSON object.
    '''
    # A left brace, followed by a string of comma-separated key-value pairs
    # with optional whitespace around items, followed by a right brace.
    assert stream.next() == '{'
    result = {}
    _skip_ws(stream)
    _assert_not_end(stream)
    if stream.peek() == ',':
        _raise_unexpected_token(stream)
    while stream.peek() != '}':
        if len(result) > 0:
            if stream.peek() != ',':
                _raise_unexpected_token(stream)
            stream.next()
            _skip_ws(stream)
        key, value = _key_value(stream)
        result[key] = value
        _skip_ws(stream)
        _assert_not_end(stream)
    stream.next()
    return result


def _json(stream: _Cursor):
    '''
    Parses and returns a JSON item (object or list).
    '''
    # A list or object surrounded by optional whitespace.
    _skip_ws(stream)
    char = stream.peek()
    if char is None:
        return None
    if char == '[':
        result = _list(stream)
    elif char == '{':
        result = _object(stream)
    else:
        _raise_unexpected_token(stream)
    _skip_ws(stream)
    if stream.peek() is not None:
        _raise_unexpected_token(stream)
    return result


def load(s: str):
    '''
    Returns a Python list or dictionary representing the JSON item encoded in
    the given string.
    '''
    cursor = _Cursor(s, 0)
    parsed = _json(cursor)
    return parsed
