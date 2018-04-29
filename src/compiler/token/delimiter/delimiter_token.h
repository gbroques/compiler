#ifndef DELIMITER_TOKEN_H
#define DELIMITER_TOKEN_H

#include <set>
#include <string>
#include "../index.h"

class DelimiterToken : public Token
{
    public:
        static bool is_delimiter(char character);
        static bool is_dot_token(Token token);
        static bool is_left_parentheses_token(Token token);
        static bool is_right_parentheses_token(Token token);
        static bool is_comma_token(Token token);
        static bool is_left_curly_brace_token(Token token);
        static bool is_right_curly_brace_token(Token token);
        static bool is_semi_colon_token(Token token);
        static bool is_left_square_bracket_token(Token token);
        static bool is_right_square_bracket_token(Token token);
        DelimiterToken(std::string value, int line_number);
        DelimiterToken(char value);

    private:
        static std::set<char> delimiters;
};

#endif