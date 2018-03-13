#ifndef TOKEN_INDEX_H
#define TOKEN_INDEX_H

#include <string>

typedef enum {
    DelimeterTokenId = 1000,
    EndOfFileTokenIdId = 1001,
    IdentifierTokenId = 1002,
    IntegerTokenId = 1003,
    OperatorTokenId = 1004,
    DefaultTokenTypeId = 1005
} TokenTypeId;

class Token
{
    public:
        Token();
        Token(TokenTypeId typeId, std::string value, int line_number);

    private:
        TokenTypeId typeId;
        std::string value;
        int line_number;
};

#endif