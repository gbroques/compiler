#include "compiler.h"

#include "frontend/frontend.h"
#include "backend/backend.h"


void Compiler::compile(std::string filename)
{
    Parser parser(filename);
    Node* parse_tree = parser.parse();

    std::string basename = get_basename(filename);
    Backend backend(basename);
    backend.traverse(parse_tree);
    
    Optimizer optimizer;
    optimizer.optimize(basename + ASM_EXT);
    
    Node::destroy(parse_tree);
}

std::string Compiler::get_basename(std::string filename)
{
    size_t last_index = filename.find_last_of('.');
    return filename.substr(0, last_index);
}