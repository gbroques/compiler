#include "keyword_token.h"

const std::string START = "start";
const std::string END = "end";
const std::string ITER = "iter";
const std::string VOID = "void";
const std::string VAR = "var";
const std::string RETURN = "return";
const std::string READ = "read";
const std::string PRINT = "print";
const std::string PROGRAM = "program";
const std::string IF = "if";
const std::string THEN = "then";
const std::string LET = "let";

bool KeywordToken::is_keyword(std::string string)
{
    return keywords.find(string) != keywords.end();
}

bool KeywordToken::is_start_token(Token token)
{
    KeywordToken start_token = KeywordToken(START);
    return token == start_token;
}

bool KeywordToken::is_end_token(Token token)
{
    KeywordToken end_token = KeywordToken(END);
    return token == end_token;
}

bool KeywordToken::is_iter_token(Token token)
{
    KeywordToken iter_token = KeywordToken(ITER);
    return token == iter_token;
}

bool KeywordToken::is_void_token(Token token)
{
    KeywordToken void_token = KeywordToken(VOID);
    return token == void_token;
}

bool KeywordToken::is_var_token(Token token)
{
    KeywordToken var_token = KeywordToken(VAR);
    return token == var_token;
}

bool KeywordToken::is_return_token(Token token)
{
    KeywordToken return_token = KeywordToken(RETURN);
    return token == return_token;
}

bool KeywordToken::is_read_token(Token token)
{
    KeywordToken read_token = KeywordToken(READ);
    return token == read_token;
}

bool KeywordToken::is_print_token(Token token)
{
    KeywordToken print_token = KeywordToken(PRINT);
    return token == print_token;
}

bool KeywordToken::is_program_token(Token token)
{
    KeywordToken program_token = KeywordToken(PROGRAM);
    return token == program_token;
}

bool KeywordToken::is_if_token(Token token)
{
    KeywordToken if_token = KeywordToken(IF);
    return token == if_token;
}

bool KeywordToken::is_then_token(Token token)
{
    KeywordToken then_token = KeywordToken(THEN);
    return token == then_token;
}

bool KeywordToken::is_let_token(Token token)
{
    KeywordToken let_token = KeywordToken(LET);
    return token == let_token;
}

KeywordToken::KeywordToken(std::string value, int line_number)
: Token(KeywordTokenId, value, line_number) {}

KeywordToken::KeywordToken(std::string value)
: Token(KeywordTokenId, value) {}

std::set<std::string> KeywordToken::keywords = {
    START,
    END,
    ITER,
    VOID,
    VAR,
    RETURN,
    READ,
    PRINT,
    PROGRAM,
    IF,
    THEN,
    LET
};