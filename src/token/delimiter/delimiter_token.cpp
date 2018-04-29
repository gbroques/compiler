#include "delimiter_token.h"

const char DOT = '.';
const char LEFT_PARENTHESES = '(';
const char RIGHT_PARENTHESES = ')';
const char COMMA = ',';
const char LEFT_CURLY_BRACE = '{';
const char RIGHT_CURLY_BRACE = '}';
const char SEMI_COLON = ';';
const char LEFT_SQUARE_BRACKET = '[';
const char RIGHT_SQUARE_BRACKET = ']';

bool DelimiterToken::is_delimiter(char character)
{
    return delimiters.find(character) != delimiters.end();
}

bool DelimiterToken::is_dot_token(Token token)
{
    Token dot_token = DelimiterToken(DOT);
    return token == dot_token;
}

bool DelimiterToken::is_left_parentheses_token(Token token)
{
    Token left_parentheses_token = DelimiterToken(LEFT_PARENTHESES);
    return token == left_parentheses_token;
}

bool DelimiterToken::is_right_parentheses_token(Token token)
{
    Token right_parentheses_token = DelimiterToken(RIGHT_PARENTHESES);
    return token == right_parentheses_token;
}

bool DelimiterToken::is_comma_token(Token token)
{
    Token comma_token = DelimiterToken(COMMA);
    return token == comma_token;
}

bool DelimiterToken::is_left_curly_brace_token(Token token)
{
    Token left_curly_brace_token = DelimiterToken(LEFT_CURLY_BRACE);
    return token == left_curly_brace_token;
}

bool DelimiterToken::is_right_curly_brace_token(Token token)
{
    Token right_curly_brace_token = DelimiterToken(RIGHT_CURLY_BRACE);
    return token == right_curly_brace_token;
}

bool DelimiterToken::is_semi_colon_token(Token token)
{
    Token semi_colon_token = DelimiterToken(SEMI_COLON);
    return token == semi_colon_token;
}

bool DelimiterToken::is_left_square_bracket_token(Token token)
{
    Token left_square_bracket_token = DelimiterToken(LEFT_SQUARE_BRACKET);
    return token == left_square_bracket_token;
}

bool DelimiterToken::is_right_square_bracket_token(Token token)
{
    Token right_square_bracket_token = DelimiterToken(RIGHT_SQUARE_BRACKET);
    return token == right_square_bracket_token;
}

DelimiterToken::DelimiterToken(std::string value, int line_number)
: Token(DelimiterTokenId, value, line_number) {}

DelimiterToken::DelimiterToken(char value)
: Token(DelimiterTokenId, value) {}

std::set<char> DelimiterToken::delimiters = {
    DOT,
    LEFT_PARENTHESES,
    RIGHT_PARENTHESES,
    COMMA,
    LEFT_CURLY_BRACE,
    RIGHT_CURLY_BRACE,
    SEMI_COLON,
    LEFT_SQUARE_BRACKET,
    RIGHT_SQUARE_BRACKET
};