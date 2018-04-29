#ifndef STATE_TRANSITION_TABLE_H
#define STATE_TRANSITION_TABLE_H

#include <vector>
#include <string>

#include "table_errors.h"

#define COMMENT_CHAR '!'
#define COMMENT_STATE 9

class StateTransitionTable
{
    public:
        static int get_next_state(int current_state, char character);
        static bool is_intermediate_state(int state);
        static bool is_final_state(int state);
        static bool is_error_state(int state);
        static bool is_invalid_char(char character);
        static bool is_valid_char(char character);
        static void print_error(int error, int line_number);
        static void print_invalid_char_error(char character, int line_number);
        static Token get_token(int state, std::string string, int line_number);

    private:
        static int get_column_index(char character);
        static const std::vector<std::vector<int>> table;
        static std::string get_error_message(int error);
        static std::string get_base_error_message();
};

#endif