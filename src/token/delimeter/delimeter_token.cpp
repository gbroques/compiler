#include "delimeter_token.h"

bool DelimeterToken::is_delimeter(char character)
{
    return delimeters.find(character) != delimeters.end();
}

DelimeterToken::DelimeterToken(std::string value, int line_number)
: Token(DelimeterTokenId, value, line_number) {}

std::set<char> DelimeterToken::delimeters = {
    ':',
    '#',
    '.',
    '(',
    ')',
    ',',
    '{',
    '}',
    ';',
    '[',
    ']'
};