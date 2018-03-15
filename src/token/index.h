#ifndef TOKEN_INDEX_H
#define TOKEN_INDEX_H

#include <string>
#include <fstream>
#include "token_type_id/token_type_id.h"

class Token
{
    public:
        Token();
        Token(TokenTypeId typeId, std::string value, int line_number);
        bool is_eof();
    
    private:
        TokenTypeId typeId;
        std::string value;
        int line_number;
        friend std::ostream& operator<<(std::ostream&, const Token&);
};

#endif