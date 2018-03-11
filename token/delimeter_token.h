#ifndef DELIMETER_TOKEN_H
#define DELIMETER_TOKEN_H

#include "token.h"

class DelimeterToken
{
    public:
        DelimeterToken(std::string value, int line_number);
    
    private:
        Token token;
};

#endif