#include "table_errors.h"

bool is_table_error(int num)
{
    switch (num) {
        case InvalidCharacter:
        case InvalidTransition:
        case MaxIntegerLength:
        case MaxIdentifierLength:
            return true;
        default:
            return false;
    }
}