#ifndef KEYWORD_TOKEN_H
#define KEYWORD_TOKEN_H

#include <set>
#include <string>
#include "../index.h"

class KeywordToken : public Token
{
    public:
        static bool is_keyword(std::string string);
        KeywordToken(std::string value, int line_number);

    private:
        static std::set<std::string> keywords;
};

#endif