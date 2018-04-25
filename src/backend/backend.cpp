#include "backend.h"
#include <iostream>

const std::set<std::string> Backend::new_scope_labels = {BLOCK, IFSTAT, LOOP};
const std::set<std::string> Backend::labels_containing_expr = {ASSIGN, OUT};

Backend::Backend()
{
    var_count = 0;
}

void Backend::traverse(Node* node)
{
    if (node == NULL) {
        return;
    }

    if (introduces_new_scope(node)) {
        var_stack.push();
        code_generator.print_to_target(PUSH);
    }

    check_for_variables(node);

    check_for_print_statements(node);

    check_for_r_letter(node);


    if (does_not_contain_expression(node)) {
        traverse_children(node);
    }

    if (introduces_new_scope(node)) {
        for (int i = 0; i < var_count; i++) {
            code_generator.print_to_target(POP);
        }
        var_count = 0;
        var_stack.pop();
        code_generator.print_to_target(POP);
    }

    if (node->label == START) {
        code_generator.print_to_target(STOP);
        code_generator.set_temp_vars_to_zero();
    }
}

void Backend::check_for_variables(Node* node)
{
    std::vector<Token> id_tokens = node->get_identifier_tokens();

    for (auto id_token : id_tokens) {
        if (contains_variable_declarations(node)) {
            int location = var_stack.find(id_token);
            if (location == 0) {
                std::string msg = "Duplicate variable declaration";
                print_error_and_exit(msg, id_token);
            }
            code_generator.print_to_target(PUSH);
            var_stack.insert(id_token);
            var_count++;
        } else {
            int location = var_stack.find(id_token);
            if (location == -1) {
                std::string msg = "Undeclared variable";
                print_error_and_exit(msg, id_token);
            }
            check_for_assignments(node, location);
            check_for_input_statements(node, location);
        }
    }
}

void Backend::print_error_and_exit(std::string msg, Token token)
{
    std::cerr << msg << " " << token << std::endl;
    exit(EXIT_FAILURE);
}

void Backend::traverse_children(Node* node)
{
    std::vector<Node*> children = node->children;
    for (unsigned int i = 0; i < children.size(); i++) {
        traverse(children.at(i));
    }
}

bool Backend::introduces_new_scope(Node* node)
{
    return new_scope_labels.count(node->label) == 1;
}

bool Backend::contains_variable_declarations(Node* node)
{
    return node->label == VARS;
}

bool Backend::does_not_contain_expression(Node* node)
{
    return !contains_expression(node);
}

bool Backend::contains_expression(Node* node)
{
    return labels_containing_expr.count(node->label) == 1;
}

void Backend::check_for_assignments(Node* node, int location)
{
    if (node->label == ASSIGN) {
        traverse_children(node);
        std::string str = STACK_WRITE + " " + std::to_string(location);
        code_generator.print_to_target(str);
    }
}

void Backend::check_for_input_statements(Node* node, int location)
{
    if (node->label == IN) {
        std::string temp_var = code_generator.get_temp_var();
        std::string str = READ + " " + temp_var;
        code_generator.print_to_target(str);
        str = LOAD + " " + temp_var;
        code_generator.print_to_target(str);
        str = STACK_WRITE + " " + std::to_string(location);
        code_generator.print_to_target(str);
    }
}

void Backend::check_for_r_letter(Node* node)
{
    if (node->label == R_LETTER) {
        for (auto token : node->tokens) {
            if (token.is_identifier()) {
                int location = var_stack.find(token);
                std::string str = STACK_READ + " " + std::to_string(location);
                code_generator.print_to_target(str);
            }
            if (token.is_integer()) {
                std::string str = LOAD + " " + token.get_value();
                code_generator.print_to_target(str);
            }
        }
    }
}

void Backend::check_for_print_statements(Node* node)
{
    if (node->label == OUT) {
        traverse_children(node);
        std::string temp_var = code_generator.get_temp_var();
        code_generator.print_to_target(STORE + " " + temp_var);
        code_generator.print_to_target(WRITE + " " + temp_var);
    }
}