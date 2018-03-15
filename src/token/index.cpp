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

bool Token::is_eof()
{
    return this->typeId == EndOfFileTokenId;
}

std::ostream& operator<<(std::ostream &strm, const Token &t) {
    std::string token_type = get_token_type_name(t.typeId);
    return strm << token_type << "(" << t.value << ") on line " << t.line_number;
}