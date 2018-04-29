#include "backend.h"
#include <iostream>

const std::set<std::string> Backend::new_scope_labels = {BLOCK, IFSTAT, LOOP};
const std::set<std::string> Backend::labels_containing_expr = {ASSIGN, OUT, IFSTAT, LOOP};

Backend::Backend(std::string base_filename)
{
    code_generator = new CodeGenerator(base_filename);
}

void Backend::traverse(Node* node)
{
    if (node == NULL) {
        return;
    }

    if (introduces_new_scope(node)) {  // Entering a scope
        var_stack.push();
        code_generator->print_to_target(PUSH);
    }

    check_for_variables(node);

    check_for_print_statements(node);

    check_for_negation(node);

    check_for_r_letter(node);

    check_for_expr(node);

    check_for_ifstat(node);

    check_for_loop(node);

    if (does_not_contain_expression(node)) {
        traverse_children(node);
    }

    if (introduces_new_scope(node)) {  // Exiting a scope
        pop_vars_in_current_scope();
        var_stack.pop();
        code_generator->print_to_target(POP);
    }

    if (node->label == START) {
        pop_vars_in_current_scope();  // Print POP for all global vars
        code_generator->print_to_target(STOP);
        code_generator->set_temp_vars_to_zero();
        code_generator->close_target();
    }
}

void Backend::pop_vars_in_current_scope()
{
    int num_vars_in_current_scope = var_stack.num_vars_in_current_scope();
    for (int i = 0; i < num_vars_in_current_scope; i++) {
        code_generator->print_to_target(POP);
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
            code_generator->print_to_target(PUSH);
            var_stack.insert(id_token);
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


void Backend::traverse_child(Node* node, int child_index)
{
    Node* child = node->children[child_index];
    traverse_children(child);
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
    return labels_containing_expr.count(node->label) == 1 ||
           (node->label == EXPR && node->children.size() == 2) ||  // <expr> -> <H> does not contain <expr>
           (node->label == HASH && node->tokens.size() == 1);
}

void Backend::check_for_assignments(Node* node, int location)
{
    if (node->label == ASSIGN) {
        traverse_children(node);
        std::string str = STACK_WRITE + " " + std::to_string(location);
        code_generator->print_to_target(str);
    }
}

void Backend::check_for_input_statements(Node* node, int location)
{
    if (node->label == IN) {
        std::string temp_var = code_generator->get_temp_var();
        std::string str = READ + " " + temp_var;
        code_generator->print_to_target(str);
        str = LOAD + " " + temp_var;
        code_generator->print_to_target(str);
        str = STACK_WRITE + " " + std::to_string(location);
        code_generator->print_to_target(str);
    }
}

void Backend::check_for_negation(Node* node)
{
    if (node->label == HASH && node->tokens.size() == 1) {
        traverse_children(node);
        code_generator->print_to_target(MULT + " -1");
    }
}

void Backend::check_for_r_letter(Node* node)
{
    if (node->label == R_LETTER) {
        for (auto token : node->tokens) {
            if (token.is_identifier()) {
                int location = var_stack.find(token);
                std::string str = STACK_READ + " " + std::to_string(location);
                code_generator->print_to_target(str);
            }
            if (token.is_integer()) {
                std::string str = LOAD + " " + token.get_value();
                code_generator->print_to_target(str);
            }
        }
    }
}

void Backend::check_for_expr(Node* node)
{
    if (node->label == EXPR and node->children.size() == 2) {
        traverse_child(node, 1);

        std::string temp_var = code_generator->get_and_store_temp_var();

        traverse_child(node, 0);

        Token operator_token = node->tokens[0];
        std::string operation = get_operation(operator_token);

        code_generator->print_to_target(operation + " " + temp_var);
    }
}

std::string Backend::get_operation(Token operator_token)
{
    std::string operation;
    if (OperatorToken::is_addition_token(operator_token)) {
        operation = ADD;
    } else if (OperatorToken::is_subtraction_token(operator_token)) {
        operation = SUB;
    } else if (OperatorToken::is_multiplication_token(operator_token)) {
        operation = MULT;
    } else if (OperatorToken::is_division_token(operator_token)) {
        operation = DIV;
    }
    return operation;
}

void Backend::check_for_print_statements(Node* node)
{
    if (node->label == OUT) {
        traverse_children(node);
        std::string temp_var = code_generator->get_and_store_temp_var();
        code_generator->print_to_target(WRITE + " " + temp_var);
    }
}

void Backend::check_for_ifstat(Node* node)
{
    if (node->label == IFSTAT) {
        std::string label = code_generator->get_label();

        evaluate_condition(node, label);

        code_generator->print_label(label);
    }
}

void Backend::check_for_loop(Node* node)
{
    if (node->label == LOOP) {
        std::string loop_label = code_generator->get_label();
        std::string out_label = code_generator->get_label();

        code_generator->print_label(loop_label);

        evaluate_condition(node, out_label);
        
        code_generator->print_to_target(BREAK + " " + loop_label);
        code_generator->print_label(out_label);
    }
}

std::vector<std::string> Backend::get_break_conditions(Token relational_operator)
{
    std::vector<std::string> break_conditions;
    if (OperatorToken::is_less_than_token(relational_operator)) {
        break_conditions.push_back(BREAK_ZERO_OR_POSITIVE);
    } else if (OperatorToken::is_greater_than_token(relational_operator)) {
        break_conditions.push_back(BREAK_ZERO_OR_NEGATIVE);
    } else if (OperatorToken::is_equals_token(relational_operator)) {
        break_conditions.push_back(BREAK_NEGATIVE);
        break_conditions.push_back(BREAK_POSITIVE);
    }
    return break_conditions;
}

/**
 * Evaluates conditions for <ifstat> and <loop> nodes
 */
void Backend::evaluate_condition(Node* node, std::string out_label)
{
    traverse_child(node, 2);

    std::string temp_var = code_generator->get_and_store_temp_var();

    traverse_child(node, 0);

    code_generator->print_to_target(SUB + " " + temp_var);

    Node* second_child = node->children[1];
    Token relational_operator = second_child->tokens[0];

    std::vector<std::string> break_conditions = get_break_conditions(relational_operator);
    for (auto break_condition : break_conditions) {
        code_generator->print_to_target(break_condition + " " + out_label);
    }

    traverse_child(node, 3);
}