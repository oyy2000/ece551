#include <iostream>
#include "Story.hpp"

int main(int argc, char **argv) {
    // throw error when arguments number is not enough
    if (argc != 2) {
        printErrorAndExit("Usage: ./cyoa-step4 {dirName}");
    }

    Story story(argv[1]);
    story.printAllPath();
    return EXIT_SUCCESS;
}