#include "end_of_file_token.h"

EndOfFileToken::EndOfFileToken(std::string value, int line_number)
: Token(EndOfFileTokenIdId, value, line_number) {}
