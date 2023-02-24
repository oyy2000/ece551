#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <set>

class Category {
public:
    std::set< std::string > words;
    std::string catName;
    std::map< std::string, std::set< std::string > > category;

public:
    std::map< std::string, std::set< std::string > > getCatArr() {
        return category;
    }
    void split(const std::string &line, const std::string &delim) {
        //先将要切割的字符串从string类型转换为char*类型
        char *strs = new char[line.length() + 1]; //不要忘了
        strcpy(strs, line.c_str());
        char *d = new char[delim.length() + 1];
        strcpy(d, delim.c_str());
        char *p = strtok(strs, d);
        std::string catName = p; //分割得到的字符串转换为string类型
        p = strtok(NULL, d);
        std::string word = p; //分割得到的字符串转换为string类型
        category[catName].insert(word);
    }

    void parseWordsList(const std::string &fileName) {
        std::ifstream inFile;
        inFile.open(fileName, std::ios::in);
        if (!inFile) {
            std::cerr << "Failed to open" << std::endl;
        }
        std::string line;
        while (getline(inFile, line)) {
            split(line, ":");
        }
    }
    void printCategory() {
        std::map< std::string, std::set< std::string > >::iterator mapIt;
        std::set< std::string >::iterator setIt;
        std::string name = "time";
        for (mapIt = category.begin(); mapIt != category.end(); mapIt++) {
            std::cout << mapIt->first << ": " << std::endl;
            for (setIt = category[mapIt->first].begin(); setIt != category[mapIt->first].end(); setIt++) {
                std::cout << "\t" << *setIt << std::endl;
            }
        }
    }
};

int main() {
    Category cat;
    const std::string wordListName = "words.txt";
    cat.parseWordsList(wordListName);
    cat.printCategory();
    std::map< std::string, std::set< std::string > > catArr;
    catArr = cat.getCatArr();
}
