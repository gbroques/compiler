#ifndef OPERATOR_TOKEN_H
#define OPERATOR_TOKEN_H

#include "token.h"

class OperatorToken
{
    public:
        OperatorToken(std::string value, int line_number);
    
    private:
        Token token;
};

#endif