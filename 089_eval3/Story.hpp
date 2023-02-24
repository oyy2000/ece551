#include "Page.hpp"
#include "tools.hpp"
#include <sstream>
#include <set>
#include <queue>
#include <stack>

/**
 * @brief the class contains all information about whole story
 *
 */
class Story {
private:
    std::vector< Page > pages;
    std::set< size_t > allPageIndexes;

public:
    /**
     * @brief Construct a new Story object
     *
     * @param dirName
     */
    explicit Story(std::string dirName) {
        size_t pageIndex = 1;
        while (true) {
            std::stringstream ss;
            ss << dirName << "/page" << pageIndex << ".txt";
            std::string pageName = ss.str();
            // check file exist
            std::ifstream pageFile(pageName);
            if (!pageFile) {
                if (pageIndex == 1) {
                    printErrorAndExit("There's no page 1.");
                } else {
                    break;
                }
            }
            pageFile.close();
            // parse page
            Page page(pageName, pageIndex);
            allPageIndexes.insert(pageIndex);
            pages.push_back(page);
            pageIndex++;
        }
        checkOutOfRange();
        checkPagesReferenced();
        checkWinLose();
    };

    // check page is out of range
    void checkOutOfRange() {
        for (size_t i = 0; i < pages.size(); ++i) {
            for (size_t j = 0; j < pages[i].getNextPages().size(); ++j) {
                if (pages[i].getNextPages()[j] > pages.size()) {
                    printErrorAndExit("There is one choice out of range!");
                }
            }
        }
    }

    /**
     * @brief using queue to search the whole pages inside story to define the depth of them(BFS)
     */
    void checkReachable() {
        long depth = 0;
        std::queue< Page > pagesQueue;
        std::vector< size_t >::iterator it;
        // set the first node of queue and begin to deque with it
        pages[0].setVisited(true);
        pages[0].setDepth(depth);
        pagesQueue.push(pages[0]);

        while (!pagesQueue.empty()) {
            depth = pagesQueue.front().getDepth();
            // get the queue head node which is the high level node
            std::vector< size_t > nextPages = pagesQueue.front().getNextPages();
            pagesQueue.pop();

            for (it = nextPages.begin(); it != nextPages.end(); ++it) {
                // if the node is referenced by current node, check if it is visited and push it into the tail of queue
                if (!(pages[(*it) - 1].getVisited())) {
                    pages[(*it) - 1].setVisited(true);
                    pages[(*it) - 1].setDepth(depth + 1);
                    pagesQueue.push(pages[(*it) - 1]);
                }
            }
        }
    }

    /**
     * @brief print Depth of each page
     */
    void printDepth() {
        for (size_t i = 0; i < pages.size(); i++) {
            long int depth = pages[i].getDepth();
            if (depth != -1) {
                std::cout << "Page " << i + 1 << ":" << depth << std::endl;
            } else {
                std::cout << "Page " << i + 1 << " is not reachable" << std::endl;
            }
        }
    }

    /**
     * @brief using recursion (DFS) to search the whole pages inside story to define the path of win
     *
     * @param index the index of page
     * @param paths contains all the result path
     * @param path contains all the node to win page
     * @param choice contain all the choice to win page
     * @param choices contains all the result choices
     * @param visited determines if the page has been visited
     */
    void DFS(size_t index, std::vector< std::vector< size_t > > &paths,
             std::vector< size_t > &path, std::vector< size_t > &choice,
             std::vector< std::vector< size_t > > &choices, std::vector< bool > &visited) {
        path.push_back(index);
        visited[index - 1] = true;
        // if reach the win page, then store an answer
        if (pages[index - 1].getPageType() == WIN_PAGE) {
            std::vector< size_t > ansPath(path);
            std::vector< size_t > ansChoice(choice);
            paths.push_back(ansPath);
            choices.push_back(ansChoice);
            // the path node need to be pop and reset to not visited
            path.pop_back();
            visited[index - 1] = false;
            return;
        }

        // try to push next pages into the path and make to the end one by one
        std::vector< size_t > nextPages = pages[index - 1].getNextPages();
        for (size_t choice_num = 0; choice_num != nextPages.size(); ++choice_num) {
            size_t nextPageIndex = pages[index - 1].parseChoicetoIndex(choice_num + 1);

            if (visited[nextPageIndex - 1] == false) {
                choice.push_back(choice_num + 1);
                DFS(nextPageIndex, paths, path, choice, choices, visited);
                choice.pop_back();
            }
        }
        // each time to return, pop the current node and reset to not visited
        path.pop_back();
        visited[index - 1] = false;
        return;
    }

    /**
     * @brief print all paths
     */
    void printAllPath() {
        // initial the variables
        std::vector< std::vector< size_t > > paths, choices;
        std::vector< size_t > path, choice;
        std::vector< bool > visited(pages.size());
        for (size_t i = 0; i < visited.size(); i++) {
            visited[i] = false;
        }
        // use DFS
        DFS(1, paths, path, choice, choices, visited);

        // print the paths
        if (paths.size() == 0) {
            std::cout << "This story is unwinnable!" << std::endl;
        } else if (paths.size() > 0) {
            for (size_t i = 0; i < paths.size(); i++) {
                for (size_t j = 0; j < paths[i].size(); j++) {
                    std::cout << paths[i][j];
                    if (pages[paths[i][j] - 1].getPageType() == WIN_PAGE) {
                        std::cout << "(win)";
                    } else {
                        std::cout << "(" << choices[i][j] << ")" << ',';
                    }
                }
                std::cout << std::endl;
            }
        }
    }
    /**
     * @brief check if there is a win page of lose page in whole story
     */
    void checkWinLose() {
        typename std::vector< Page >::iterator it = pages.begin();
        int winPagesNum = 0;
        int losePageNum = 0;
        while (it != pages.end()) {
            if (it->getPageType() == WIN_PAGE) {
                winPagesNum++;
            }
            if (it->getPageType() == LOSE_PAGE) {
                losePageNum++;
            }
            it++;
        }
        if (winPagesNum == 0 || losePageNum == 0) {
            printErrorAndExit("At least one page must be a WIN page and at least one page must be a LOSE page.");
        }
    }

    /**
     * @brief if all pages are valid and referenced
     */
    void checkPagesReferenced() {
        connectPages();
        // check referencing from page 1
        for (size_t i = 0; i < pages.size(); i++) {
            Page &currentPage = pages[i];
            std::vector< size_t > nextPages = currentPage.getNextPages();
            for (size_t j = 0; j < nextPages.size(); j++) {
                size_t pageIndex = nextPages[j];
                if (allPageIndexes.find(pageIndex) == allPageIndexes.end()) {
                    printErrorAndExit("some pages are not valid!");
                }
            }
        }
        // check referenced skip page 1
        for (size_t i = 1; i < pages.size(); i++) {
            std::set< size_t > prevPages = pages[i].getPrevPages();
            if (prevPages.empty() == true) {
                printErrorAndExit("some pages are not referenced!");
            }
        }
    }

    /**
     * @brief fill prevPages for all pages
     */
    void connectPages() {
        for (size_t i = 0; i < pages.size(); i++) {
            std::vector< size_t > nextPages = pages[i].getNextPages();
            for (size_t j = 0; j < nextPages.size(); j++) {
                size_t pageIndex = nextPages[j];
                // fill the prevPages for this target page
                pages[pageIndex - 1].insertPrevPages(pages[i].getPageIndex());
            }
        }
    }

    /**
     * @brief print prompt "That is not a valid choice, please try again"
     */
    void printPrompt() {
        std::cout << "That is not a valid choice, please try again" << std::endl;
    }

    /**
     * @brief  display story and accept cin
     */
    void displayStory() {
        size_t choiceNum;
        size_t pageIndex = 1;

        int pageType = pages[pageIndex - 1].getPageType();
        std::string choiceInput;
        while (pageType != WIN_PAGE && pageType != LOSE_PAGE) {
            pages[pageIndex - 1].printSinglePage();
            /**
             * format the input
             * If the input is not a number, or it is not valid for the choices on the
             * page, prompt the user ("That is not a valid choice, please try again") and
             * read another number. Repeat until they give a valid choice.
             */
            while (getline(std::cin, choiceInput).good()) {
                if (std::cin.eof()) {
                    printErrorAndExit("Unexpected EOF!");
                }
                if (!std::cin.eof() && !std::cin) {
                    printErrorAndExit("Fail to read data from cin!");
                }
                // the input is empty
                if (choiceInput.empty()) {
                    printPrompt();
                    continue;
                }
                // the input is not a valid number
                if (isNumber(choiceInput) == false) {
                    printPrompt();
                    continue;
                }
                char *ptr;
                choiceNum = strtoul(choiceInput.c_str(), &ptr, 10);
                if (choiceNum == 0 || errno == ERANGE || choiceNum > pages[pageIndex - 1].getNextPages().size()) {
                    printPrompt();
                    continue;
                }
                break;
            }

            pageIndex = pages[pageIndex - 1].parseChoicetoIndex(choiceNum);
            pageType = pages[pageIndex - 1].getPageType();
        }
        pages[pageIndex - 1].printSinglePage();
    }
};