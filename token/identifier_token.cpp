#include "identifier_token.h"

IdentifierToken::IdentifierToken(std::string value, int line_number)
{
    Token token(Identifier, value, line_number);
}
