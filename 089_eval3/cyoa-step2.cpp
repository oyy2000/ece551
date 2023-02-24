#include <iostream>
#include "Story.hpp"

int main(int argc, char **argv) {
    // throw error when arguments number is not enough
    if (argc != 2) {
        printErrorAndExit("Usage: ./cyoa-step2 {dirName}");
    }

    Story story(argv[1]);
    story.displayStory();
    return EXIT_SUCCESS;
}