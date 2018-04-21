#ifndef STATIC_SEMANTICS_H
#define STATIC_SEMANTICS_H

#include <set>
#include <string>

#include "../parser/parser.h"
#include "var_stack.h"


class SemanticAnalyzer
{
    public:
        void analyze(Node* parse_tree);

    private:
        VarStack var_stack;
        static std::set<std::string> new_scope_labels;
        void traverse(Node* node);
        void check_for_variables(Node* node);
        void print_error_and_exit(Token token);
        void traverse_children(Node* node);
        static bool introduces_new_scope(Node* node);
        static bool contains_variable_declarations(Node* node);
};



#endif