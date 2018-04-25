#include "index.h"

Token::Token()
{
    this->typeId = DefaultTokenTypeId;
    this->value = "";
    this->line_number = 0;
}

Token::Token(TokenTypeId typeId, std::string value, int line_number)
{
    this->typeId = typeId;
    this->value = value;
    this->line_number = line_number;
}

Token::Token(TokenTypeId typeId, std::string value)
{
    this->typeId = typeId;
    this->value = value;
    this->line_number = 0;
}

Token::Token(TokenTypeId typeId, char value)
{
    std::string string_value(1, value);
    
    this->typeId = typeId;
    this->value = string_value;
    this->line_number = 0;
}

bool Token::is_eof()
{
    return this->typeId == EndOfFileTokenId;
}

bool Token::is_identifier()
{
    return this->typeId == IdentifierTokenId;
}

bool Token::is_integer()
{
    return this->typeId == IntegerTokenId;
}

std::string Token::get_value()
{
    return value;
}

std::ostream& operator<<(std::ostream &stream, const Token &token)
{
    std::string token_type = get_token_type_name(token.typeId);
    return stream << token_type << "(" << token.value << ") on line " << token.line_number;
}

bool operator==(const Token &t1, const Token &t2)
{
    return t1.typeId == t2.typeId && t1.value == t2.value;
}

bool operator!=(const Token &t1, const Token &t2)
{
    return t1.typeId != t2.typeId || t1.value != t2.value;
}

bool operator<(const Token &t1, const Token &t2)
{
    return t1.value < t2.value;
}