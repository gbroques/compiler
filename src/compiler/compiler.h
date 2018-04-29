#ifndef COMPILER_H
#define COMPILER_H

#include <string>

class Compiler
{
    public:
        void compile(std::string filename);

    private:
        std::string get_basename(std::string filename);
};

#endif