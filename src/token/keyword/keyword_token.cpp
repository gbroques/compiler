#include "keyword_token.h"

bool KeywordToken::is_keyword(std::string string)
{
    return keywords.find(string) != keywords.end();
}

KeywordToken::KeywordToken(std::string value, int line_number)
: Token(KeywordTokenId, value, line_number) {}

std::set<std::string> KeywordToken::keywords = {
    "start",
    "end",
    "iter",
    "void",
    "var",
    "return",
    "read",
    "print",
    "program",
    "if",
    "then",
    "let"
};