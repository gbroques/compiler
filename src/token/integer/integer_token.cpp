#include "integer_token.h"

bool IntegerToken::is_integer(char character)
{
    return isdigit(character);
}

IntegerToken::IntegerToken(std::string value, int line_number)
: Token(IntegerTokenId, value, line_number) {}
