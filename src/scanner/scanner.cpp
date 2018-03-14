#include <fstream>
#include <iostream>
#include <string>
#include "scanner.h"
#include "state_transition_table/state_transition_table.h"

FiniteAutomatonDriver::FiniteAutomatonDriver(std::string filename)
{
    file = open_file(filename);
    line_number = 0;
    next_char = ' ';
}

FiniteAutomatonDriver::~FiniteAutomatonDriver()
{
    close_file();
}

Token FiniteAutomatonDriver::read()
{
    int state = 0;
    int next_state = StateTransitionTable::get_next_state(state, next_char);
    std::string string = "";
    
    while (StateTransitionTable::is_intermediate_state(next_state)) {
        next_state = StateTransitionTable::get_next_state(state, next_char);

        check_for_table_error(next_state);

        if (StateTransitionTable::is_final_state(next_state)) {
            return StateTransitionTable::get_token(next_state, string, line_number);
        } else {
            state = next_state;
            if (!isspace(next_char)) {
                string += next_char;
            }
        }
        if (next_char == '\n') {
            line_number++;
        }
        file >> std::noskipws >> next_char;
    }
}

void FiniteAutomatonDriver::check_for_table_error(int state)
{
    if (is_table_error(state)) {
        StateTransitionTable::print_error(state, line_number);
        exit(1);
    }
}

std::ifstream FiniteAutomatonDriver::open_file(std::string filename)
{
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Cannot open file '" << filename << "'.\n";
        exit(1);
    }
    return file;
}

void FiniteAutomatonDriver::close_file()
{
    file.close();
}