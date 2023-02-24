#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

void printIfstream(ifstream &read)
{
    std::string aString;
    std::vector<std::string> strings;
    while (!read.eof())
    {
        std::getline(read, aString);
        strings.push_back(aString);
    }
    std::sort(strings.begin(), strings.end());
    std::vector<std::string>::iterator it = strings.begin();
    while (it != strings.end())
    {
        std::cout << *it << std::endl;
        it++;
    }
    strings.clear();
}

void printIstream(istream &read)
{
    std::string aString;
    std::vector<std::string> strings;
    while (!read.eof())
    {
        std::getline(read, aString);
        strings.push_back(aString);
    }
    std::sort(strings.begin(), strings.end());
    std::vector<std::string>::iterator it = strings.begin();
    while (it != strings.end())
    {
        std::cout << *it << std::endl;
        it++;
    }
    strings.clear();
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        printIstream(cin);
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            std::ifstream read(argv[i]);
            if (read.fail())
            {
                std::cerr << "Can't open file: " << argv[i] << std::endl;
                exit(EXIT_FAILURE);
            }
            printIfstream(read);
        }
    }
    return EXIT_SUCCESS;
}