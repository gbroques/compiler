#include "delimeter_token.h"

DelimeterToken::DelimeterToken(std::string value, int line_number)
{
    Token token(Delimeter, value, line_number);
}
