#ifndef TABLE_ERRORS_H
#define TABLE_ERRORS_H

typedef enum {
    InvalidTransition = -10,
    MaxIntegerLength = -20,
    MaxIdentifierLength = -30
} StateTransitionTableErrors;

bool is_table_error(int num);

#endif