#include "end_of_file_token.h"

EndOfFileToken::EndOfFileToken(std::string value, int line_number)
{
    Token token(EndOfFile, value, line_number);
}
