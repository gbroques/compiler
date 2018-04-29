#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>

#include "../token/token.h"
#include "node_labels.h"

class Node
{
    public:
        static Node* of(std::string label, int level);
        static void destroy(Node* node);
        void append_child(Node* child);
        void append_token(Token token);
        static void print(Node* node);
        std::vector<Token> get_identifier_tokens();
        std::vector<Node*> children;
        std::string label;
        std::vector<Token> tokens;
        int level;
    
    private:
        static void print_node(Node* node);
        static void print_children(Node* node);
        friend std::ostream& operator<<(std::ostream&, const Node&);
};

#endif