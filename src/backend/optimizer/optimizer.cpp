#include "optimizer.h"

#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include "../target_keywords.h"
#include <stdio.h>

void Optimizer::optimize(std::string target_filename)
{
    target.open(target_filename);
    std::ofstream tmp;
    std::string tmp_filename = "tmp" + target_filename;
    tmp.open(tmp_filename);

    std::string prev_line;
    std::string line;
    while (std::getline(target, line)) {
        bool print_to_tmp = true;
        if (is_line(prev_line, STACK_WRITE) && is_line(line, STACK_READ)) {
            std::vector<std::string> prev_words = split_line(prev_line);
            std::vector<std::string> words = split_line(line);
            int prev_location = to_int(words[1]);
            int location = to_int(words[1]);
            if (prev_location == location) {
                print_to_tmp = false;
            }
        }
        if (print_to_tmp) {
            tmp << line << std::endl;
        }
        prev_line = line;
    }
    std::getline(target, line);

    tmp.close();
    target.close();

    if (remove(target_filename.c_str()) != 0) {
        perror("Error deleting file");
    }

    if (rename(tmp_filename.c_str(), target_filename.c_str()) != 0) {
        perror("Error renaming file");
    }
}

bool Optimizer::is_line(std::string line, std::string target_keyword)
{
    return line.find(target_keyword) != std::string::npos;
}

std::vector<std::string> Optimizer::split_line(std::string line)
{
    std::istringstream iss(line);
    std::vector<std::string> words((std::istream_iterator<std::string>(iss)),
                                     std::istream_iterator<std::string>());
    return words;
}

int Optimizer::to_int(std::string str)
{
    int num;
    std::istringstream iss(str);
    iss >> num;
    return num;
}