#include "operator_token.h"

bool OperatorToken::is_operator(char character)
{
    return operators.find(character) != operators.end();
}

OperatorToken::OperatorToken(std::string value, int line_number)
: Token(OperatorTokenId, value, line_number) {}

std::set<char> OperatorToken::operators = {
    '+',
    '-',
    '*',
    '/',
    '<',
    '>'
};
