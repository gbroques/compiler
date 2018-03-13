#ifndef DELIMETER_TOKEN_H
#define DELIMETER_TOKEN_H

#include "../index.h"

class DelimeterToken : public Token
{
    public:
        DelimeterToken(std::string value, int line_number);
};

#endif