#include "index.h"

Token::Token()
{
    this->value = "";
    this->line_number = 0;
}

Token::Token(TokenType type, std::string value, int line_number)
{
    this->type = type;
    this->value = value;
    this->line_number = line_number;
}