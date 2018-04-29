#ifndef OPERATOR_TOKEN_H
#define OPERATOR_TOKEN_H

#include <set>
#include <string>
#include "../index.h"

class OperatorToken : public Token
{
    public:
        static bool is_operator(char character);
        static bool is_addition_token(Token token);
        static bool is_subtraction_token(Token token);
        static bool is_multiplication_token(Token token);
        static bool is_division_token(Token token);
        static bool is_negation_token(Token token);
        static bool is_less_than_token(Token token);
        static bool is_greater_than_token(Token token);
        static bool is_equals_token(Token token);
        static bool is_assignment_token(Token token);
        OperatorToken(std::string value, int line_number);
        OperatorToken(char value);

    private:
        static std::set<char> operators;
};

#endif