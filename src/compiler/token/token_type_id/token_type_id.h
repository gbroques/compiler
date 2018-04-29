#ifndef TOKEN_TYPE_ID_H
#define TOKEN_TYPE_ID_H

#include <string>

typedef enum {
    DelimiterTokenId = 1000,
    EndOfFileTokenId = 1001,
    IdentifierTokenId = 1002,
    IntegerTokenId = 1003,
    KeywordTokenId = 1004,
    OperatorTokenId = 1005,
    DefaultTokenTypeId = 1006
} TokenTypeId;

bool is_token_type_id(int num);

std::string get_token_type_name(int id);

#endif