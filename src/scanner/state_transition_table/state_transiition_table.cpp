#include <iostream>
#include "../../token/token.h"
#include "state_transition_table.h"

int StateTransitionTable::get_next_state(int current_state, char character)
{
    int column_index = get_column_index(character);
    return table[current_state][column_index];
}

int StateTransitionTable::get_column_index(char character)
{
    if (IntegerToken::is_integer(character)) {
        return 0;
    } else if (COMMENT_CHAR == character) {
        return 1;
    } else if (OperatorToken::is_operator(character)) {
        return 2;
    } else if (DelimeterToken::is_delimeter(character)) {
        return 3;
    } else if (islower(character) && isalpha(character)) {
        return 4;
    } else if (isupper(character) && isalpha(character)) {
        return 5;
    } else if (EndOfFileToken::is_eof(character)) {
        return 6;
    } else if (isspace(character)) {
        return 7;
    }
}

bool StateTransitionTable::is_intermediate_state(int state)
{
    return !is_final_state(state);
}

bool StateTransitionTable::is_final_state(int state)
{
    return is_token_type_id(state);
}

void StateTransitionTable::print_error(int error, int line_number)
{
    std::string message = get_error_message(error);
    message.append(" on line " + line_number);
    std::cerr << "Scanner Error: " << message << std::endl;
}

std::string StateTransitionTable::get_error_message(int error)
{
    std::string message;
    switch (error) {
        case InvalidTransition:
            message = "Invalid transition.";
            break;
        case MaxIntegerLength:
            message = "Maximum integer length exceeded.";
            break;
        case MaxIdentifierLength:
            message = "Maximum integer length exceeded.";
            break;
    }
    return message;
}

Token StateTransitionTable::get_token(int state, std::string string, int line_number)
{
    switch (state) {
        case DelimeterTokenId:
            return DelimeterToken(string, line_number);
        case EndOfFileTokenId:
            return EndOfFileToken(string, line_number);
        case IdentifierTokenId:
            if (KeywordToken::is_keyword(string)) {
                return KeywordToken(string, line_number);
            } else {
                return IdentifierToken(string, line_number);
            }
        case IntegerTokenId:
            return IntegerToken(string, line_number);
        case OperatorTokenId:
            return OperatorToken(string, line_number);
    }
}

const std::vector<std::vector<int>> StateTransitionTable::table = {
    {1, 9, 10, 11, 12, InvalidTransition, EndOfFileTokenId, 0},
    {2, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId},
    {3, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId},
    {4, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId},
    {5, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId},
    {6, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId},
    {7, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId},
    {8, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId},
    {9, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId},
    {MaxIntegerLength, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId, IntegerTokenId},
    {OperatorTokenId, OperatorTokenId, OperatorTokenId, OperatorTokenId, OperatorTokenId, OperatorTokenId, OperatorTokenId, OperatorTokenId},
    {DelimeterTokenId, DelimeterTokenId, DelimeterTokenId, DelimeterTokenId, DelimeterTokenId, DelimeterTokenId, DelimeterTokenId, DelimeterTokenId},
    {13, IdentifierTokenId, IdentifierTokenId, IdentifierTokenId, 13, 13, IdentifierTokenId, IdentifierTokenId},
    {14, IdentifierTokenId, IdentifierTokenId, IdentifierTokenId, 14, 14, IdentifierTokenId, IdentifierTokenId},
    {15, IdentifierTokenId, IdentifierTokenId, IdentifierTokenId, 15, 15, IdentifierTokenId, IdentifierTokenId},
    {16, IdentifierTokenId, IdentifierTokenId, IdentifierTokenId, 16, 16, IdentifierTokenId, IdentifierTokenId},
    {17, IdentifierTokenId, IdentifierTokenId, IdentifierTokenId, 17, 17, IdentifierTokenId, IdentifierTokenId},
    {18, IdentifierTokenId, IdentifierTokenId, IdentifierTokenId, 18, 18, IdentifierTokenId, IdentifierTokenId},
    {19, IdentifierTokenId, IdentifierTokenId, IdentifierTokenId, 19, 19, IdentifierTokenId, IdentifierTokenId},
    {MaxIdentifierLength, IdentifierTokenId, IdentifierTokenId, IdentifierTokenId, MaxIdentifierLength, MaxIdentifierLength, IdentifierTokenId, IdentifierTokenId}
};