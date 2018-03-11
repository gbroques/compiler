#include <vector>
#include <string>

class StateTransitionTable
{
    private:
        static const std::vector<std::vector<std::string>> table;
};

typedef enum {
    InvalidTransition = -10,
    MaxIntegerLength = -20,
    MaxIdentifierLength = -30
} StateTransitionTableErrors;