#ifndef TOKEN_INDEX_H
#define TOKEN_INDEX_H

#include <string>
#include <fstream>
#include "token_type_id/token_type_id.h"

class Token
{
    public:
        static bool is_identifier(int type_id);
        Token();
        Token(TokenTypeId typeId, std::string value, int line_number);
    
    private:
        TokenTypeId typeId;
        std::string value;
        int line_number;
        friend std::ostream& operator<<(std::ostream&, const Token&);
};

#endif