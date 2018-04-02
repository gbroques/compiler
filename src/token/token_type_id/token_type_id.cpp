#include "token_type_id.h"

bool is_token_type_id(int num)
{
    switch (num) {
        case DelimiterTokenId:
        case EndOfFileTokenId:
        case IdentifierTokenId:
        case IntegerTokenId:
        case KeywordTokenId:
        case OperatorTokenId:
        case DefaultTokenTypeId:
            return true;
        default:
            return false;
    }
}

std::string get_token_type_name(int id)
{
    switch (id) {
        case DelimiterTokenId:
            return "DelimeterToken";
        case EndOfFileTokenId:
            return "EndOfFileToken";
        case IdentifierTokenId:
            return "IdentifierToken";
        case IntegerTokenId:
            return "IntegerToken";
        case KeywordTokenId:
            return "KeywordToken";
        case OperatorTokenId:
            return "OperatorToken";
        default:
            return "DefaultToken";
    }  
}