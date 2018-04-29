#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "timer.h"
#include "parser/parser.h"
#include "backend/backend.h"
#include "backend/optimizer/optimizer.h"

std::string get_filename(int argc, char** argv);

int main(int argc, char** argv) 
{
    timer timer_ = timer();
    timer_.start("Timer started.");

    std::string filename = get_filename(argc, argv);
    
    Parser parser(filename);
    Node* parse_tree = parser.parse();
    size_t lastindex = filename.find_last_of(".");
    std::string basename = filename.substr(0, lastindex);
    
    Backend backend(basename);
    backend.traverse(parse_tree);
    
    Optimizer optimizer;
    optimizer.optimize(basename + ASM_EXT);
    
    Node::destroy(parse_tree);

    std::cout << "OK\n";

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