#include "token.h"

Token::Token()
{
    this->value = "";
    this->line_number = 0;
}

Token::Token(TokenTypeId typeId, std::string value, int line_number)
{
    this->typeId = typeId;
    this->value = value;
    this->line_number = line_number;
}