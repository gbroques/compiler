#include "code_generator.h"
#include <stdarg.h>

CodeGenerator::CodeGenerator()
{
    target.open("a.asm");
    temp_count = 0;
}

CodeGenerator::~CodeGenerator()
{
    target.close();
}

void CodeGenerator::print_to_target(std::string str)
{
    target << str << std::endl;
}

std::string CodeGenerator::get_temp_var()
{
    std::string temp_var = T + std::to_string(temp_count);
    temp_count++;
    return temp_var;
}

void CodeGenerator::set_temp_vars_to_zero()
{
    for (int i = 0; i < temp_count; i++) {
        target << T << i << " 0\n";
    }
}
