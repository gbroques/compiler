#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token
{
    public:
        Token();
        Token(std::string value, int line_number);

    private:
        std::string value;
        int line_number;
};

#include "delimeter_token.h"
#include "eof_token.h"
#include "identifier_token.h"
#include "integer_token.h"
#include "operator_token.h"

#endif