#ifndef DELIMETER_TOKEN_H
#define DELIMETER_TOKEN_H

#include <set>
#include <string>
#include "../index.h"

class DelimeterToken : public Token
{
    public:
        static bool is_delimeter(char character);
        DelimeterToken(std::string value, int line_number);

    private:
        static std::set<char> delimeters;
};

#endif