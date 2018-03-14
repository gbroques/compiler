#ifndef OPERATOR_TOKEN_H
#define OPERATOR_TOKEN_H

#include <set>
#include <string>
#include "../index.h"

class OperatorToken : public Token
{
    public:
        static bool is_operator(char character);
        OperatorToken(std::string value, int line_number);

    private:
        static std::set<char> operators;
};

#endif