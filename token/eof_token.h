#ifndef EOF_TOKEN_H
#define EOF_TOKEN_H

#include "token.h"

class EOFToken
{
    public:
        EOFToken(std::string value, int line_number);
    
    private:
        Token token;
};

#endif