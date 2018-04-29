#include <fstream>
#include <iostream>
#include <string>

#include "scanner.h"
#include "state_transition_table/state_transition_table.h"

Scanner::Scanner(std::string filename)
{
    file.open(filename);
    check_file(file, filename);
    line_number = 1;
    next_char = ' ';
    is_eof_reached = false;
}

Scanner::~Scanner()
{
    close_file();
}

void Scanner::check_file(std::ifstream& file, std::string filename)
{
    if (!file) {
        std::cerr << "Error: Cannot open file '" << filename << "'.\n";
        exit(1);
    }
}

void Scanner::close_file()
{
    file.close();
}

Token Scanner::read()
{
    int state = 0;
    int next_state = StateTransitionTable::get_next_state(state, next_char);
    std::string string = "";

    do {
        check_for_eof();
        
        check_for_invalid_character(state);

        next_state = StateTransitionTable::get_next_state(state, next_char);

        check_for_table_error(next_state);

        if (StateTransitionTable::is_final_state(next_state)) {
            return StateTransitionTable::get_token(next_state, string, line_number);
        } else {
            state = next_state;
            if (!isspace(next_char) && next_char != COMMENT_CHAR && state != COMMENT_STATE) {
                string += next_char;
            }
        }
        if (next_char == '\n') {
            line_number++;
        }
    } while (file >> std::noskipws >> next_char || !is_eof_reached);

    return EndOfFileToken(line_number);
}

void Scanner::check_for_invalid_character(int state)
{
    if (StateTransitionTable::is_invalid_char(next_char) && state != COMMENT_STATE) {
        StateTransitionTable::print_invalid_char_error(next_char, line_number);
        exit(1);
    }
}

void Scanner::check_for_table_error(int state)
{
    if (is_table_error(state)) {
        StateTransitionTable::print_error(state, line_number);
        exit(1);
    }
}

/**
 * Since we can't read in an EOF character,
 * we need to read in some last character to
 * properly recognize tokens at the end of a file.
 * The space ' ' character is arbitrary.
 */
void Scanner::check_for_eof()
{
    if (file.eof()) {
        next_char = ' ';
        is_eof_reached = true;
    }
}