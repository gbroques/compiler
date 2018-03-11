#ifndef TOKEN_INDEX_H
#define TOKEN_INDEX_H

#include <string>

typedef enum {
    Delimeter = 1000,
    EndOfFile = 1001,
    Identifier = 1002,
    Integer = 1003,
    Operator = 1004,
    DefaultTokenType = 1005
} TokenType;

class Token
{
    public:
        Token();
        Token(TokenType type, std::string value, int line_number);

    private:
        TokenType type;
        std::string value;
        int line_number;
};

#endif