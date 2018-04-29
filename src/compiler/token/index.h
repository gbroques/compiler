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
        Token(TokenTypeId typeId, std::string value);
        Token(TokenTypeId typeId, char value);
        bool is_eof();
        bool is_identifier();
        bool is_integer();
        std::string get_value();
        
    private:
        TokenTypeId typeId;
        std::string value;
        int line_number;
        friend std::ostream& operator<<(std::ostream&, const Token&);
        friend bool operator==(const Token&, const Token&);
        friend bool operator!=(const Token&, const Token&);
        friend bool operator<(const Token&, const Token&);
};

#endif