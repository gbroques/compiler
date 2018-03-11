#include "token/token.h"
#include "state_transition_table.h"

const std::vector<std::vector<int>> table = {
    {1, 9, 10, 11, 12, InvalidTransition, EndOfFile, 0},
    {2, Integer, Integer, Integer, Integer, Integer, Integer, Integer},
    {3, Integer, Integer, Integer, Integer, Integer, Integer, Integer},
    {4, Integer, Integer, Integer, Integer, Integer, Integer, Integer},
    {5, Integer, Integer, Integer, Integer, Integer, Integer, Integer},
    {6, Integer, Integer, Integer, Integer, Integer, Integer, Integer},
    {7, Integer, Integer, Integer, Integer, Integer, Integer, Integer},
    {8, Integer, Integer, Integer, Integer, Integer, Integer, Integer},
    {9, Integer, Integer, Integer, Integer, Integer, Integer, Integer},
    {MaxIntegerLength, Integer, Integer, Integer, Integer, Integer, Integer, Integer},
    {Operator, Operator, Operator, Operator, Operator, Operator, Operator, Operator},
    {Delimeter, Delimeter, Delimeter, Delimeter, Delimeter, Delimeter, Delimeter, Delimeter},
    {13, Identifier, Identifier, Identifier, 13, 13, Identifier, Identifier},
    {14, Identifier, Identifier, Identifier, 14, 14, Identifier, Identifier},
    {15, Identifier, Identifier, Identifier, 15, 15, Identifier, Identifier},
    {16, Identifier, Identifier, Identifier, 16, 16, Identifier, Identifier},
    {17, Identifier, Identifier, Identifier, 17, 17, Identifier, Identifier},
    {18, Identifier, Identifier, Identifier, 18, 18, Identifier, Identifier},
    {19, Identifier, Identifier, Identifier, 19, 19, Identifier, Identifier},
    {MaxIdentifierLength, Identifier, Identifier, Identifier, MaxIdentifierLength, MaxIdentifierLength, Identifier, Identifier}
};