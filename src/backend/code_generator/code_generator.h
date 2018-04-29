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
        void print_label(std::string label);
        std::string get_temp_var();
        std::string get_and_store_temp_var();
        std::string get_label();
        void set_temp_vars_to_zero();
        void close_target();

    private:
        int temp_var_count;  // Keep track of the number of temporary variables
        int label_count;
        std::ofstream target;
};

#endif