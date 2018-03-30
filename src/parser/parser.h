#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "../scanner/scanner.h"
#include "../token/token.h"

class Parser
{
    public:
        Parser(std::string filename);
        void parse();

    private:
        Scanner* scanner;
        Token token;
        void S();
        void block();
        void vars();
        void expr();
        void H();
        void R();
        void stats();
        void m_stat();
        void stat();
        void in();
        void out();
        void ifstat();
        void loop();
        void assign();
        void O();
        void error();
        void check_for_comma_token();
};

#endif