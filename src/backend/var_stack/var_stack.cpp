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
        int count = var_stack[i].count(var);
        if (count > 0) {
            return position_from_top_of_stack;
        }
        position_from_top_of_stack++;
    }
    return -1;
}