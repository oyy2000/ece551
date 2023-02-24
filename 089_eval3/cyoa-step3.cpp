#include <iostream>
#include "Story.hpp"

int main(int argc, char **argv) {
    // throw error when arguments number is not enough
    if (argc != 2) {
        printErrorAndExit("Usage: ./cyoa-step3 {dirName}");
    }

    Story story(argv[1]);

    story.checkReachable();
    story.printDepth();
    return EXIT_SUCCESS;
}