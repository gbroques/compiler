#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include <fstream>
#include <vector>

class Optimizer
{
    public:
        void optimize(std::string target_filename);
        bool is_line(std::string line, std::string target_keyword);
        std::vector<std::string> split_line(std::string line);
        int to_int(std::string str);

    private:
        std::ifstream target;
};

#endif