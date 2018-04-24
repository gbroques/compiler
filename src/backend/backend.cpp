#include "backend.h"

void Backend::traverse(Node* parse_tree)
{
    semantic_analyzer.analyze(parse_tree);
}