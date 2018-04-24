#ifndef BACKEND_H
#define BACKEND_H

#include "../parser/parser.h"
#include "semantic_analyzer/semantic_analyzer.h"

/**
 * Backend part of compiler responsible for:
 *   - static semantics
 *   - storage allocation
 *   - and code generation
 */
class Backend
{
    public:
        void traverse(Node* parse_tree);
    
    private:
        SemanticAnalyzer semantic_analyzer;
};

#endif