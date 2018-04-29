#include "node.h"
#include <algorithm>
#include <iostream>

Node* Node::of(std::string label, int level)
{
    Node* node = new Node();
    node->label = label;
    node->level = level;
    return node;
}

void Node::append_child(Node* child)
{
    this->children.push_back(child);
}

void Node::append_token(Token token)
{
    this->tokens.push_back(token);
}

void Node::destroy(Node* node)
{
    if (node == NULL) {
        return;
    }
    std::vector<Node*> children = node->children;
    std::for_each(children.begin(), children.end(), &destroy);
    delete node;
}

void Node::print(Node* node)
{
    if (node == NULL) {
        return;
    }

    print_node(node);

    print_children(node);
}

void Node::print_node(Node* node)
{
    printf("%*c%d:%-9s ", node->level, ' ', node->level, node->label.c_str());
    for (auto i = node->tokens.begin(); i != node->tokens.end(); ++i)
        std::cout << *i << ' ';
    printf("\n");
}

void Node::print_children(Node* node)
{
    std::vector<Node*> children = node->children;
    for (unsigned int i = 0; i < children.size(); i++) {
        print(children.at(i));
    }
}

std::vector<Token> Node::get_identifier_tokens()
{
    std::vector<Token> identifier_tokens;
    for (auto token : tokens) {
        if (token.is_identifier()) {
            identifier_tokens.push_back(token);
        }
    }
    return identifier_tokens;
}


std::ostream& operator<<(std::ostream &stream, const Node &node)
{
    return stream << node.label;
}
