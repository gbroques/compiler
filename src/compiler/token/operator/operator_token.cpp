#include <string>
#include "operator_token.h"

const char ADDITION = '+';
const char SUBTRACTION = '-';
const char MULTIPLICATION = '*';
const char DIVISION = '/';
const char NEGATION = '#';
const char LESS_THAN = '<';
const char GREATER_THAN = '>';
const char ASSIGNMENT = '=';
const char EQUALS = ':';

bool OperatorToken::is_operator(char character)
{
    return operators.find(character) != operators.end();
}

bool OperatorToken::is_addition_token(Token token)
{
    Token addition_token = OperatorToken(ADDITION);
    return token == addition_token;
}

bool OperatorToken::is_subtraction_token(Token token)
{
    Token subtraction_token = OperatorToken(SUBTRACTION);
    return token == subtraction_token;
}

bool OperatorToken::is_multiplication_token(Token token)
{
    Token multiplication_token = OperatorToken(MULTIPLICATION);
    return token == multiplication_token;
}

bool OperatorToken::is_division_token(Token token)
{
    Token division_token = OperatorToken(DIVISION);
    return token == division_token;
}

bool OperatorToken::is_negation_token(Token token)
{
    Token negation_token = OperatorToken(NEGATION);
    return token == negation_token;
}

bool OperatorToken::is_less_than_token(Token token)
{
    Token less_than_token = OperatorToken(LESS_THAN);
    return token == less_than_token;
}

bool OperatorToken::is_greater_than_token(Token token)
{
    Token greater_than_token = OperatorToken(GREATER_THAN);
    return token == greater_than_token;
}

bool OperatorToken::is_equals_token(Token token)
{
    Token equals_token = OperatorToken(EQUALS);
    return token == equals_token;
}

bool OperatorToken::is_assignment_token(Token token)
{
    Token assignment_token = OperatorToken(ASSIGNMENT);
    return token == assignment_token;
}

OperatorToken::OperatorToken(std::string value, int line_number)
: Token(OperatorTokenId, value, line_number) {}

OperatorToken::OperatorToken(char value)
: Token(OperatorTokenId, value) {}

std::set<char> OperatorToken::operators = {
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    NEGATION,
    LESS_THAN,
    GREATER_THAN,
    EQUALS,
    ASSIGNMENT
};
