#include "var_stack.h"
#include <iostream>

VarStack::VarStack()
{
    var_stack.emplace_back();
}

void VarStack::push()
{
    var_stack.emplace_back();
}

void VarStack::pop()
{
    var_stack.pop_back();
}

void VarStack::insert(Token var)
{
    var_stack.back().insert(var);
}

void VarStack::erase(Token var)
{
    var_stack.back().erase(var);
}

/**
 * Finds a variable and returns the distance from the top of the stack.
 * 
 * Returns -1 if not found.
 */
int VarStack::find(Token var)
{
    int position_from_top_of_stack = 0;
    for (int i = var_stack.size() - 1; i >= 0; i--) {
        std::set<Token> tokens = var_stack[i];
        for (auto token = tokens.rbegin(); token != tokens.rend(); ++token) {
            if (var == *token) {
                return position_from_top_of_stack;
            }
            position_from_top_of_stack++;
        }
        position_from_top_of_stack++;
    }
    return -1;
}

int VarStack::num_vars_in_current_scope()
{
    std::set<Token> current_scope = var_stack[var_stack.size() - 1];
    return current_scope.size();
}