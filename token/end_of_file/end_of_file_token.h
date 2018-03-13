#ifndef EOF_TOKEN_H
#define EOF_TOKEN_H

#include "../index.h"

class EndOfFileToken : public Token
{
    public:
        EndOfFileToken(std::string value, int line_number);
};

#endif