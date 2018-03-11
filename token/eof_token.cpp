#include "eof_token.h"

EOFToken::EOFToken(std::string value, int line_number)
{
    Token token(value, line_number);
}
