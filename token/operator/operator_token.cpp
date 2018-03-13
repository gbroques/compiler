#include "operator_token.h"

OperatorToken::OperatorToken(std::string value, int line_number)
: Token(OperatorTokenId, value, line_number) {}
