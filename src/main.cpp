#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "timer.h"
#include "parser/parser.h"
#include "semantic_analyzer/semantic_analyzer.h"

std::string get_filename(int argc, char** argv);

int main(int argc, char** argv) 
{
    timer timer_ = timer();
    timer_.start("Timer started.");

    std::string filename = get_filename(argc, argv);
    
    Parser parser(filename);
    Node* parse_tree = parser.parse();

    SemanticAnalyzer semantic_analyzer = SemanticAnalyzer();
    Node::print(parse_tree);
    semantic_analyzer.analyze(parse_tree);


    Node::destroy(parse_tree);

    timer_.stop("Timer stopped.");

    std::cout << "Total elapsed time: " << timer_.timeVal() << " seconds.\n";

    return 0;
}

std::string get_filename(int argc, char** argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(1);
    }
    std::string filename(argv[1]);
    return filename;
}