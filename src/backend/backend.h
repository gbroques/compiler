#ifndef BACKEND_H
#define BACKEND_H

#include "../parser/parser.h"
#include "var_stack/var_stack.h"

/**
 * Backend part of compiler responsible for:
 *   - static semantics
 *   - storage allocation
 *   - and code generation
 */
class Backend
{
    public:
        void traverse(Node* node);

    private:
        VarStack var_stack;
        static std::set<std::string> new_scope_labels;
        void check_for_variables(Node* node);
        void check_location(int location, std::string err_msg, Token token);
        void print_error_and_exit(std::string msg, Token token);
        void traverse_children(Node* node);
        static bool introduces_new_scope(Node* node);
        static bool contains_variable_declarations(Node* node);
};

#endif