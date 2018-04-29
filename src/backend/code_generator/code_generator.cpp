#include "code_generator.h"
#include <stdarg.h>

CodeGenerator::CodeGenerator(std::string base_filename)
{
    target.open(base_filename + ASM_EXT);
    temp_var_count = 0;
    label_count = 0;
}

CodeGenerator::~CodeGenerator()
{
    target.close();
}

void CodeGenerator::print_to_target(std::string str)
{
    target << str << std::endl;
}

void CodeGenerator::print_label(std::string label)
{
    target << label << ": NOOP" << std::endl;
}

std::string CodeGenerator::get_temp_var()
{
    std::string temp_var = TEMP_VAR_PREFIX + std::to_string(temp_var_count);
    temp_var_count++;
    return temp_var;
}

std::string CodeGenerator::get_and_store_temp_var()
{
    std::string temp_var = get_temp_var();
    print_to_target(STORE + " " + temp_var);
    return temp_var;
}

void CodeGenerator::set_temp_vars_to_zero()
{
    for (int i = 0; i < temp_var_count; i++) {
        target << TEMP_VAR_PREFIX << i << " 0\n";
    }
}

std::string CodeGenerator::get_label()
{
    std::string label = LABEL_PREFIX + std::to_string(label_count);
    label_count++;
    return label;
}

void CodeGenerator::close_target()
{
    target.close();
}
