#include "index.h"

bool Token::is_identifier(int type_id)
{
    return type_id == IdentifierTokenId;
}

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

std::ostream& operator<<(std::ostream &strm, const Token &t) {
    return strm << "Token(" << t.value << ")";
}