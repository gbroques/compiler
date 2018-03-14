#ifndef IDENTIFIER_TOKEN_H
#define IDENTIFIER_TOKEN_H

#include <string>
#include "../index.h"

class IdentifierToken : public Token
{
    public:
        IdentifierToken(std::string value, int line_number);
};

#endif