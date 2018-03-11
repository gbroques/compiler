#include "operator_token.h"

OperatorToken::OperatorToken(std::string value, int line_number)
{
    Token token(Operator, value, line_number);
}
