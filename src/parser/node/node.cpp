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

std::ostream& operator<<(std::ostream &stream, const Node &node) {
    return stream << node.label;
}

void Node::print(Node* node)
{
    if (node == NULL) {
        return;
    }

    printf("%*c%d:%-9s ", node->level, ' ', node->level, node->label.c_str());
    for (auto i = node->tokens.begin(); i != node->tokens.end(); ++i)
        std::cout << *i << ' ';
    printf("\n");

    std::vector<Node*> children = node->children;
    for (unsigned int i = 0; i < children.size(); i++) {
        print(children.at(i));
    }
}