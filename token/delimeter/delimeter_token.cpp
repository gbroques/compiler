#include "delimeter_token.h"

DelimeterToken::DelimeterToken(std::string value, int line_number)
: Token(DelimeterTokenId, value, line_number) {}
