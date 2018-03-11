#ifndef INTEGER_TOKEN_H
#define INTEGER_TOKEN_H

#include "index.h"

class IntegerToken
{
    public:
        IntegerToken(std::string value, int line_number);
    
    private:
        Token token;
};

#endif