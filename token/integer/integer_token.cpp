#include "integer_token.h"

IntegerToken::IntegerToken(std::string value, int line_number)
: Token(IntegerTokenId, value, line_number) {}
