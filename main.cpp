#include <iostream>
#include <string>
#include <fstream>

std::string get_filename(int argc, char** argv);
std::ifstream open_file(std::string filename);


int main(int argc, char** argv) 
{
    std::string filename = get_filename(argc, argv);

    std::ifstream file = open_file(filename);

    file.close();

    return 0;
}

std::string get_filename(int argc, char** argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(1);
    }
    std::string filename(argv[1]);
    return filename;
}

std::ifstream open_file(std::string filename)
{
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Cannot open file '" << filename << "'.\n";
        exit(1);
    }
    return file;
}