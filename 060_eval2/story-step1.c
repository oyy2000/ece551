#include "rand_story.h"

/**
 * @brief Parse the story template by printing
 * the story and replacing blanks with the word "cat"
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char **argv) {
    if (argc != 2) {
        printErrorAndExit("Usage: ./{prog_name} {story_txt_file_name}!!\n");
    }
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        printErrorAndExit("Fail to open the file!\n");
    }
    // parse the story
    parseStory(NULL, f, NULL, -1);
    if (fclose(f) != 0) {
        printErrorAndExit("Fail to close the file!\n");
    }
    return EXIT_SUCCESS;
}