#include "semantic_analyzer.h"
#include <iostream>

std::set<std::string> SemanticAnalyzer::new_scope_labels = {BLOCK, IFSTAT, LOOP};


void SemanticAnalyzer::analyze(Node* parse_tree)
{
    traverse(parse_tree);
}

void SemanticAnalyzer::traverse(Node* node)
{
    if (node == NULL) {
        return;
    }

    if (introduces_new_scope(node)) {
        var_stack.push();
    }

    check_for_variables(node);
    
    traverse_children(node);

    if (introduces_new_scope(node)) {
        var_stack.pop();
    }
}

void SemanticAnalyzer::check_for_variables(Node* node)
{
    std::vector<Token> id_tokens = node->get_identifier_tokens();

    for (auto id_token : id_tokens) {
        if (contains_variable_declarations(node)) {
            int location = var_stack.find(id_token);
            if (location != -1) {
                print_duplicate_declaration_error_and_exit(id_token);
            }
            var_stack.insert(id_token);
        } else {
            int location = var_stack.find(id_token);
            if (location == -1) {
                print_undeclared_error_and_exit(id_token);
            }
        }
    }
}

void SemanticAnalyzer::print_duplicate_declaration_error_and_exit(Token token)
{
    std::cerr << "Duplicate variable declaration " << token << std::endl;
    exit(EXIT_FAILURE);
}

void SemanticAnalyzer::print_undeclared_error_and_exit(Token token)
{
    std::cerr << token << " undeclared. First use in this scope.\n";
    exit(EXIT_FAILURE);
}

void SemanticAnalyzer::traverse_children(Node* node)
{
    std::vector<Node*> children = node->children;
    for (unsigned int i = 0; i < children.size(); i++) {
        traverse(children.at(i));
    }
}

bool SemanticAnalyzer::introduces_new_scope(Node* node)
{
    return new_scope_labels.count(node->label) == 1;
}

bool SemanticAnalyzer::contains_variable_declarations(Node* node)
{
    return node->label == VARS;
}