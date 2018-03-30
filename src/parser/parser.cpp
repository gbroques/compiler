#include <iostream>
#include "parser.h"
#include "../scanner/scanner.h"
#include "../token/token.h"

Parser::Parser(std::string filename)
{
    scanner = new Scanner(filename);
}

void Parser::parse()
{
    token = scanner->read();
    S();
    if (token.is_eof()) {
        return;
    }
    error();
}

/**
 * <S> -> program <vars> <block>
 */
void Parser::S()
{
    if (KeywordToken::is_program_token(token)) {
        token = scanner->read();
        vars();
        block();
        return;
    } else {
        error();
    }
}

/**
 * <block> -> start <vars> <stats> end
 */
void Parser::block()
{
    if (KeywordToken::is_start_token(token)) {
        token = scanner->read();
        vars();
        stats();
        if (KeywordToken::is_end_token(token)) {
            token = scanner->read();
            return;
        }
    }
    error();
}

/**
 * <vars> -> var Identifier <vars> | empty
 */
void Parser::vars()
{
    if (KeywordToken::is_var_token(token)) {
        token = scanner->read();
        if (token.is_identifier()) {
            token = scanner->read();
            vars();
            return;
        } else {
            error();
        }
    } else {
        return;
    }
}

/**
 * <expr> -> <H> + <expr> | <H> - <expr>
 * <expr> -> <H> / <expr> | <H> * <expr>
 * <expr> -> <H>
 */
void Parser::expr()
{
    H();
    if (OperatorToken::is_addition_token(token)) {
        token = scanner->read();
        expr();
        return;
    } else if (OperatorToken::is_subtraction_token(token)) {
        token = scanner->read();
        expr();
        return;
    } else if (OperatorToken::is_division_token(token)) {
        token = scanner->read();
        expr();
        return;
    } else if (OperatorToken::is_multiplication_token(token)) {
        token = scanner->read();
        expr();
        return;
    }
    return;
}

/**
 * <H> -> # <R> | <R>
 */
void Parser::H()
{
    if (DelimiterToken::is_hash_token(token)) {
        token = scanner->read();
        R();
        return;
    } else {
        R();
        return;
    }
}

/**
 * <R> -> ( <expr> ) | Identifier | Integer
 */
void Parser::R()
{
    if (DelimiterToken::is_left_parentheses_token(token)) {
        token = scanner->read();
        expr();
        if (DelimiterToken::is_right_parentheses_token(token)) {
            token = scanner->read();
            return;
        }
    } else if (token.is_identifier()) {
        token = scanner->read();
        return;
    } else if (token.is_integer()) {
        token = scanner->read();
        return;
    }
    error();
}

/**
 * <stats> -> <stat> <m_stat>
 */
void Parser::stats()
{
    stat();
    m_stat();
    return;
}

/**
 * <m_stat> -> <stats> | empty
 */
void Parser::m_stat()
{
    if (KeywordToken::is_read_token(token) ||
        KeywordToken::is_print_token(token) ||
        KeywordToken::is_start_token(token) ||
        KeywordToken::is_if_token(token) ||
        KeywordToken::is_iter_token(token) ||
        KeywordToken::is_let_token(token)) {
        stats();
    } else {
        return;
    }
}

/**
 * <stat> -> <in> , | <out> , | <block> , | <ifstat> , | <loop> , | <assign> ,
 */
void Parser::stat()
{
    if (KeywordToken::is_read_token(token)) {
        in();
        check_for_comma_token();
    } else if (KeywordToken::is_print_token(token)) {
        out();
        check_for_comma_token();
    } else if (KeywordToken::is_start_token(token)) {
        block();
        check_for_comma_token();
    } else if (KeywordToken::is_if_token(token)) {
        ifstat();
        check_for_comma_token();
    } else if (KeywordToken::is_iter_token(token)) {
        loop();
        check_for_comma_token();
    } else if (KeywordToken::is_let_token(token)) {
        assign();
        check_for_comma_token();
    }
    error();
}

void Parser::check_for_comma_token() {
    if (DelimiterToken::is_comma_token(token)) {
        token = scanner->read();
        return;
    }
}

/**
 * <in> -> read Identifier
 */
void Parser::in()
{
    if (KeywordToken::is_read_token(token)) {
        token = scanner->read();
        if (token.is_identifier()) {
            token = scanner->read();
            return;
        }
    }
    error();
}

/**
 * <out> -> print <expr>
 */
void Parser::out()
{
    if (KeywordToken::is_print_token(token)) {
        token = scanner->read();
        expr();
        return;
    }
    error();
}

/**
 * <ifstat> -> if ( <expr> <O> <expr> ) <stat>
 */
void Parser::ifstat()
{
    if (KeywordToken::is_if_token(token)) {
        token = scanner->read();
        if (DelimiterToken::is_left_parentheses_token(token)) {
            token = scanner->read();
            expr();
            O();
            expr();
            if (DelimiterToken::is_right_parentheses_token(token)) {
                token = scanner->read();
                stat();
                return;
            }
        }
    }
    error();
}

/**
 * <loop> -> iter ( <expr> <O> <expr> ) <stat>
 */
void Parser::loop()
{
    if (KeywordToken::is_iter_token(token)) {
        token = scanner->read();
        if (DelimiterToken::is_left_parentheses_token(token)) {
            token = scanner->read();
            expr();
            O();
            expr();
            if (DelimiterToken::is_right_parentheses_token(token)) {
                token = scanner->read();
                stat();
                return;
            }
        }
    }
    error();
}

/**
 * <assign> -> let Identifier = <expr>
 */
void Parser::assign()
{
    if (KeywordToken::is_let_token(token)) {
        token = scanner->read();
        if (token.is_identifier()) {
            token = scanner->read();
            if (OperatorToken::is_assignment_token(token)) {
                token = scanner->read();
                expr();
                return;
            }
        }
    }
    error();
}

/**
 * <O> -> < | > | :
 */
void Parser::O()
{
    if (OperatorToken::is_less_than_token(token)) {
        token = scanner->read();
        return;
    } else if (OperatorToken::is_greater_than_token(token)) {
        token = scanner->read();
        return;
    } else if (DelimiterToken::is_colon_token(token)) {
        token = scanner->read();
        return;
    }
    error();
}

void Parser::error()
{
    std::cerr << "Parser error: " << token << std::endl;
    exit(1);
}