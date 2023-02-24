#include "rand_story.h"

/**
 * @brief Read from the file and store the words into a
 * catarray_t and print them using the provided function printWords.
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char **argv) {
    if (argc != 2) {
        printErrorAndExit("Usage: ./{prog_name} {words_txt_file_name}!!\n");
    }
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        printErrorAndExit("Fail to open the file!\n");
    }
    // parse the words and print
    catarray_t *catArr = parseWords(f, f);
    printWords(catArr);
    freeCatArr(catArr);
    if (fclose(f) != 0) {
        printErrorAndExit("Fail to close the file!\n");
    }
    return EXIT_SUCCESS;
}