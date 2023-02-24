#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>

#include <set>
#include <cerrno>
#include "tools.hpp"

/**
 * @brief define the type of pages
 */
enum pageTypes {
    WIN_PAGE,   // 0 if WIN
    LOSE_PAGE,  // 1 if LOSE page
    NORMAL_PAGE // 2 if normal page
};

/**
 * @class the class contains all information about a page in the whole story
 * and functions that parse strings into pages
 */
class Page {
private:
    std::vector< std::pair< size_t, std::string > > pageQuestions;
    std::vector< std::string > pageContent;
    std::set< size_t > prevPages;
    std::vector< size_t > nextPages;
    pageTypes pageType;
    size_t pageIndex;
    bool visited;
    long int depth;

public:
    /**
     * @brief Construct a new Page object
     *
     * @param fileName
     * @param _pageIndex
     */
    explicit Page(const std::string fileName, size_t _pageIndex) :
        pageType(NORMAL_PAGE), pageIndex(_pageIndex), visited(false), depth(-1) {
        parseSinglePage(fileName);
    };

    /**
     * @brief extract choice number and text from a line with :
     *
     * @param line
     * @return std::pair<size_t, std::string>
     */
    std::pair< size_t, std::string > extractChoiceAndText(const std::string &line) {
        size_t splitter = line.find(':');
        // there is no ':'
        if (splitter == std::string::npos) {
            printErrorAndExit("Invalid input without ':' !");
        }
        // there is nothing before ':'
        if (splitter == 0) {
            printErrorAndExit("Invalid input without anything before ':' !");
        }

        const std::string strChoiceNum = line.substr(0, splitter);
        if (isNumber(strChoiceNum) == false) {
            printErrorAndExit("Invalid digit before ':' !");
        }
        errno = 0; // To distinguish success/failure after call
        char *ptr;
        size_t pageIndex = strtoul(strChoiceNum.c_str(), &ptr, 10);
        if (pageIndex == 0 || errno == ERANGE) {
            printErrorAndExit("Invalid number before ':' ");
        }
        std::string question = line.substr(splitter + 1, line.size() - splitter - 1);
        std::pair< size_t, std::string > data(pageIndex, question);
        nextPages.push_back(pageIndex);
        return data;
    }

    /**
     * @brief parse Choice number into page Index
     *
     * @param choice
     * @return size_t
     */
    size_t parseChoicetoIndex(int choice) {
        return pageQuestions[choice - 1].first;
    }

    /**
     * @brief parse single page with the file name
     *
     * @param fileName
     */
    void parseSinglePage(std::string fileName) {
        std::ifstream inFile;
        inFile.open(fileName.c_str(), std::ios::in);
        if (!inFile) {
            printErrorAndExit("Failed to open!");
        }
        parsePageQuestions(inFile);
        parsePageContent(inFile);
        if (!inFile.eof() && !inFile) {
            printErrorAndExit("Failed to read the file!");
        }
        inFile.close();
    }

    /**
     * @brief parse question page of a page with the file stream
     *
     * @param fileName
     */
    void parsePageQuestions(std::ifstream &inFile) {
        bool isFirstLine = true;
        std::string line;
        while (getline(inFile, line).good()) {
            // the first line maybe the WIN or LOSE sign, so treat it specially
            if (isFirstLine) {
                isFirstLine = false;
                if (line[0] == '#') {
                    printErrorAndExit("No choices before # !");
                }
                if (line.compare("WIN") == 0) {
                    pageType = WIN_PAGE;
                    pageQuestions.push_back(std::pair< size_t, std::string >(0, line));
                    continue;
                } else if (line.compare("LOSE") == 0) {
                    pageType = LOSE_PAGE;
                    pageQuestions.push_back(std::pair< size_t, std::string >(0, line));
                    continue;
                }
            }
            if (line[0] == '#') { // if navigation part ends, break and try to parse the content part
                break;
            } else { // if navigation part do not end, extract it
                pageQuestions.push_back(extractChoiceAndText(line));
            }
        }
    }

    /**
     * @brief parse content page of a page with the file stream
     *
     * @param fileName
     */
    void parsePageContent(std::ifstream &inFile) {
        std::string line;
        while (getline(inFile, line).good()) {
            pageContent.push_back(line);
        }
    }

    /**
     * @brief print the content part of page out
     */
    void printPageContent() {
        std::vector< std::string >::iterator it = pageContent.begin();
        for (; it != pageContent.end(); it++) {
            std::cout << *it << std::endl;
        }
    }

    /**
     * @brief print the question part of page out
     */
    void printPageQuestions() {
        if (pageType == WIN_PAGE) {
            std::cout << std::endl;
            std::cout << "Congratulations! You have won. Hooray!" << std::endl;
        } else if (pageType == LOSE_PAGE) {
            std::cout << std::endl;
            std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
        } else if (pageType == NORMAL_PAGE) {
            std::vector< std::pair< size_t, std::string > >::iterator it = pageQuestions.begin();
            std::cout << std::endl;
            std::cout << "What would you like to do?" << std::endl;
            std::cout << std::endl;
            for (int choiceNum = 1; it != pageQuestions.end(); it++, choiceNum++) {
                std::cout << " " << choiceNum << ". " << it->second << std::endl;
            }
        }
    }

    /**
     * @brief print whole page
     *
     */
    void printSinglePage() {
        printPageContent();
        printPageQuestions();
    }

    /**
     * @brief Set the depth of page
     *
     * @param _depth
     */
    void setDepth(long int _depth) {
        depth = _depth;
    }

    /**
     * @brief Get the depth of page
     *
     * @return long int
     */
    long int getDepth() {
        return depth;
    }

    /**
     * @brief Set the Visited attribute
     *
     * @param _visited
     */
    void setVisited(bool _visited) {
        visited = _visited;
    }

    /**
     * @brief Get the Visited attribute
     *
     * @return true
     * @return false
     */
    bool getVisited() {
        return visited;
    }

    /**
     * @brief Get the Page Index
     *
     * @return size_t
     */
    size_t getPageIndex() {
        return pageIndex;
    }

    /**
     * @brief Get the Page Type
     *
     * @return pageTypes
     */
    pageTypes getPageType() {
        return pageType;
    }

    /**
     * @brief Get the Next Pages of one page
     *
     * @return std::vector<size_t>
     */
    std::vector< size_t > getNextPages() {
        return nextPages;
    }

    /**
     * @brief insert previous Pages set
     *
     * @param pageIndex
     */
    void insertPrevPages(size_t pageIndex) {
        prevPages.insert(pageIndex);
    }

    /**
     * @brief Get the Prev Pages set
     *
     * @return std::set<size_t>
     */
    std::set< size_t > getPrevPages() {
        return prevPages;
    }

    friend class Story;
};
