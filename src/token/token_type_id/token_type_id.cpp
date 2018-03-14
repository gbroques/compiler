#include "token_type_id.h"

bool is_token_type_id(int num) {
    switch (num) {
        case DelimeterTokenId:
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