#ifndef TABLE_ERRORS_H
#define TABLE_ERRORS_H

typedef enum {
    InvalidCharacter = -10,
    InvalidTransition = -20,
    MaxIntegerLength = -30,
    MaxIdentifierLength = -40
} StateTransitionTableErrors;

bool is_table_error(int num);

#endif