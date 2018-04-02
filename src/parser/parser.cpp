#include <iostream>
#include "parser.h"
#include "../scanner/scanner.h"
#include "../token/token.h"  

Parser::Parser(std::string filename)
{
    scanner = new Scanner(filename);
}

Parser::~Parser()
{
    delete scanner;
}

Node* Parser::parse()
{
    Node* root;
    token = scanner->read();
    root = S();
    if (token.is_eof()) {
        return root;
    }
    error();
}

/**
 * <S> -> program <vars> <block>
 */
Node* Parser::S()
{
    int level = 1;
    if (KeywordToken::is_program_token(token)) {
        Node* node = Node::of("S", level);
        token = scanner->read();
        node->append_child(vars(level));
        node->append_child(block(level));
        return node;
    }
    error();
}

/**
 * <block> -> start <vars> <stats> end
 */
Node* Parser::block(int level)
{
    level++;
    if (KeywordToken::is_start_token(token)) {
        Node* node = Node::of("block", level);
        token = scanner->read();
        node->append_child(vars(level));
        node->append_child(stats(level));
        if (KeywordToken::is_end_token(token)) {
            token = scanner->read();
            return node;
        }
    }
    error();
}

/**
 * <vars> -> var Identifier <vars> | empty
 */
Node* Parser::vars(int level)
{
    if (KeywordToken::is_var_token(token)) {
        level++;
        Node* node = Node::of("vars", level);
        token = scanner->read();
        if (token.is_identifier()) {
            node->append_token(token);
            token = scanner->read();
            node->append_child(vars(level));
            return node;
        } else {
            error();
        }
    } else {
        return NULL;
    }
}

/**
 * <expr> -> <H> + <expr> | <H> - <expr>
 * <expr> -> <H> / <expr> | <H> * <expr>
 * <expr> -> <H>
 */
Node* Parser::expr(int level)
{
    level++;
    Node* node = Node::of("expr", level);
    node->append_child(H(level));
    if (OperatorToken::is_addition_token(token)) {
        node->append_token(token);
        token = scanner->read();
        node->append_child(expr(level));
        return node;
    } else if (OperatorToken::is_subtraction_token(token)) {
        node->append_token(token);
        token = scanner->read();
        node->append_child(expr(level));
        return node;
    } else if (OperatorToken::is_division_token(token)) {
        node->append_token(token);
        token = scanner->read();
        node->append_child(expr(level));
        return node;
    } else if (OperatorToken::is_multiplication_token(token)) {
        node->append_token(token);
        token = scanner->read();
        node->append_child(expr(level));
        return node;
    }
    return node;
}

/**
 * <H> -> # <R> | <R>
 */
Node* Parser::H(int level)
{
    level++;
    Node* node = Node::of("H", level);
    if (DelimiterToken::is_hash_token(token)) {
        node->append_token(token);
        token = scanner->read();
        node->append_child(R(level));
        return node;
    } else {
        node->append_child(R(level));
        return node;
    }
}

/**
 * <R> -> ( <expr> ) | Identifier | Integer
 */
Node* Parser::R(int level)
{
    level++;
    Node* node = Node::of("R", level);
    if (DelimiterToken::is_left_parentheses_token(token)) {
        token = scanner->read();
        node->append_child(expr(level));
        if (DelimiterToken::is_right_parentheses_token(token)) {
            token = scanner->read();
            return node;
        }
    } else if (token.is_identifier()) {
        node->append_token(token);
        token = scanner->read();
        return node;
    } else if (token.is_integer()) {
        node->append_token(token);
        token = scanner->read();
        return node;
    }
    error();
}

/**
 * <stats> -> <stat> <m_stat>
 */
Node* Parser::stats(int level)
{
    level++;
    Node* node = Node::of("stats", level);
    node->append_child(stat(level));
    node->append_child(m_stat(level));
    return node;
}

/**
 * <m_stat> -> <stats> | empty
 */
Node* Parser::m_stat(int level)
{
    if (is_first_of_stats(token)) {
        level++;
        Node* node = Node::of("m_stat", level);
        node->append_child(stats(level));
        return node;
    } else {
        return NULL;
    }
}

bool Parser::is_first_of_stats(Token token) {
    return KeywordToken::is_read_token(token) ||
           KeywordToken::is_print_token(token) ||
           KeywordToken::is_start_token(token) ||
           KeywordToken::is_if_token(token) ||
           KeywordToken::is_iter_token(token) ||
           KeywordToken::is_let_token(token);
}

/**
 * <stat> -> <in> , | <out> , | <block> , | <ifstat> , | <loop> , | <assign> ,
 */
Node* Parser::stat(int level)
{
    level++;
    Node* node = Node::of("stat", level);
    if (KeywordToken::is_read_token(token)) {
        node->append_child(in(level));
        check_for_comma_token();
        return node;
    } else if (KeywordToken::is_print_token(token)) {
        node->append_child(out(level));
        check_for_comma_token();
        return node;
    } else if (KeywordToken::is_start_token(token)) {
        node->append_child(block(level));
        check_for_comma_token();
        return node;
    } else if (KeywordToken::is_if_token(token)) {
        node->append_child(ifstat(level));
        check_for_comma_token();
        return node;
    } else if (KeywordToken::is_iter_token(token)) {
        node->append_child(loop(level));
        check_for_comma_token();
        return node;
    } else if (KeywordToken::is_let_token(token)) {
        node->append_child(assign(level));
        check_for_comma_token();
        return node;
    }
    error();
}

void Parser::check_for_comma_token() {
    if (DelimiterToken::is_comma_token(token)) {
        token = scanner->read();
    } else {
        error();
    }
}

/**
 * <in> -> read Identifier
 */
Node* Parser::in(int level)
{
    if (KeywordToken::is_read_token(token)) {
        level++;
        Node* node = Node::of("in", level);
        token = scanner->read();
        if (token.is_identifier()) {
            node->append_token(token);
            token = scanner->read();
            return node;
        }
    }
    error();
}

/**
 * <out> -> print <expr>
 */
Node* Parser::out(int level)
{
    level++;
    if (KeywordToken::is_print_token(token)) {
        Node* node = Node::of("out", level);
        token = scanner->read();
        node->append_child(expr(level));
        return node;
    }
    error();
}

/**
 * <ifstat> -> if ( <expr> <O> <expr> ) <stat>
 */
Node* Parser::ifstat(int level)
{
    level++;
    if (KeywordToken::is_if_token(token)) {
        Node* node = Node::of("ifstat", level);
        token = scanner->read();
        if (DelimiterToken::is_left_parentheses_token(token)) {
            token = scanner->read();
            node->append_child(expr(level));
            node->append_child(O(level));
            node->append_child(expr(level));
            if (DelimiterToken::is_right_parentheses_token(token)) {
                token = scanner->read();
                node->append_child(stat(level));
                return node;
            }
        }
    }
    error();
}

/**
 * <loop> -> iter ( <expr> <O> <expr> ) <stat>
 */
Node* Parser::loop(int level)
{
    level++;
    if (KeywordToken::is_iter_token(token)) {
        Node* node = Node::of("loop", level);
        token = scanner->read();
        if (DelimiterToken::is_left_parentheses_token(token)) {
            token = scanner->read();
            node->append_child(expr(level));
            node->append_child(O(level));
            node->append_child(expr(level));
            if (DelimiterToken::is_right_parentheses_token(token)) {
                token = scanner->read();
                node->append_child(stat(level));
                return node;
            }
        }
    }
    error();
}

/**
 * <assign> -> let Identifier = <expr>
 */
Node* Parser::assign(int level)
{
    level++;
    if (KeywordToken::is_let_token(token)) {
        Node* node = Node::of("assign", level);
        token = scanner->read();
        if (token.is_identifier()) {
            node->append_token(token);
            token = scanner->read();
            if (OperatorToken::is_assignment_token(token)) {
                token = scanner->read();
                node->append_child(expr(level));
                return node;
            }
        }
    }
    error();
}

/**
 * <O> -> < | > | :
 */
Node* Parser::O(int level)
{
    level++;
    Node* node = Node::of("O", level);
    if (is_O_token(token)) {
        node->append_token(token);
        token = scanner->read();
        return node;
    }
    error();
}

bool Parser::is_O_token(Token token) {
    return OperatorToken::is_less_than_token(token) ||
           OperatorToken::is_greater_than_token(token) ||
           DelimiterToken::is_colon_token(token);
}

void Parser::error()
{
    std::cerr << "Parser error: " << token << std::endl;
    exit(1);
}