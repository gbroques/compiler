#ifndef SCANNER_H
#define SCANNER_H

#include "../token/token.h"

class Scanner
{
    public:
        Scanner(std::string filename);
        ~Scanner();
        Token read();
    
    private:
        std::ifstream file;
        int line_number;
        char next_char;
        std::ifstream open_file(std::string filename);
        void close_file();
        void check_for_invalid_character(int state);
        void check_for_table_error(int state);
};

#endif
