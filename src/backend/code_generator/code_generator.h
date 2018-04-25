#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include <string>
#include "../target_keywords.h"
#include <fstream>

class CodeGenerator
{
    public:
        CodeGenerator();
        ~CodeGenerator();
        void print_to_target(std::string str);
        std::string get_temp_var();
        void set_temp_vars_to_zero();

    private:
        int temp_count;  // Keep track of the number of temporary variables
        std::ofstream target;
};

#endif