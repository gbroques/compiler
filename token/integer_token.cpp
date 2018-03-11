#include "integer_token.h"

IntegerToken::IntegerToken(std::string value, int line_number)
{
    Token token(Integer, value, line_number);
}
