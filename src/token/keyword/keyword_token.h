#ifndef KEYWORD_TOKEN_H
#define KEYWORD_TOKEN_H

#include <set>
#include <string>
#include "../index.h"

class KeywordToken : public Token
{
    public:
        static bool is_keyword(std::string string);
        static bool is_start_token(Token token);
        static bool is_end_token(Token token);
        static bool is_iter_token(Token token);
        static bool is_void_token(Token token);
        static bool is_var_token(Token token);
        static bool is_return_token(Token token);
        static bool is_read_token(Token token);
        static bool is_print_token(Token token);
        static bool is_program_token(Token token);
        static bool is_if_token(Token token);
        static bool is_then_token(Token token);
        static bool is_let_token(Token token);
        KeywordToken(std::string value, int line_number);
        KeywordToken(std::string value);

    private:
        static std::set<std::string> keywords;
};

#endif