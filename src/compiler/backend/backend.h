#ifndef BACKEND_H
#define BACKEND_H

#include <iostream>

#include "../node/node.h"
#include "var_stack/var_stack.h"
#include "code_generator/code_generator.h"
#include "optimizer/optimizer.h"

/**
 * Backend part of compiler responsible for:
 *   - static semantics
 *   - storage allocation
 *   - and code generation
 */

class Backend
{
    public:
        Backend(std::string base_filename);
        void traverse(Node* node);

    private:
        VarStack var_stack;
        CodeGenerator* code_generator;
        const static std::set<std::string> new_scope_labels;
        const static std::set<std::string> labels_containing_expr;
        void check_for_variables(Node* node);
        void check_location(int location, std::string err_msg, Token token);
        void print_error_and_exit(std::string msg, Token token);
        void traverse_children(Node* node);
        void pop_vars_in_current_scope();
        void traverse_child(Node* node, int child_index);
        static bool introduces_new_scope(Node* node);
        static bool contains_variable_declarations(Node* node);
        static bool contains_expression(Node* node);
        static bool does_not_contain_expression(Node* node);
        void check_for_assignments(Node* node, int location);
        void check_for_input_statements(Node* node, int location);
        void check_for_negation(Node* node);
        void check_for_r_letter(Node* node);
        void check_for_expr(Node* node);
        std::string get_operation(Token token);
        void check_for_print_statements(Node* node);
        void check_for_ifstat(Node* node);
        void check_for_loop(Node* node);
        std::vector<std::string> get_break_conditions(Token token);
        void evaluate_condition(Node* node, std::string out_label);
};

#endif