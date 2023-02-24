#include "rand_story.h"

/**
 * @brief Replace the blank with a previously used word
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char **argv) {
    if (argc != 3) {
        printErrorAndExit("Usage: ./{prog_name} {words_txt_file_name} {story_txt_file_name}!!\n");
    }
    // open the words file
    FILE *f1 = fopen(argv[1], "r");
    if (f1 == NULL) {
        if (fclose(f1) != 0) {
            printErrorAndExit("Fail to close the file!\n");
        }
        printErrorAndExit("Fail to open the file!\n");
    }
    // open the sotry file
    FILE *f2 = fopen(argv[2], "r");
    if (f2 == NULL) {
        if (fclose(f1) != 0) {
            printErrorAndExit("Fail to close the file!\n");
        }
        if (fclose(f2) != 0) {
            printErrorAndExit("Fail to close the file!\n");
        }
        printErrorAndExit("Fail to open the file!\n");
    }
    catarray_t *catArr = parseWords(f1, f2);
    parseStory(f1, f2, catArr, 0);
    freeCatArr(catArr);
    if (fclose(f1) != 0) {
        if (fclose(f2) != 0) {
            printErrorAndExit("Fail to close the file!\n");
        }
        printErrorAndExit("Fail to close the file!\n");
    }
    if (fclose(f2) != 0) {
        printErrorAndExit("Fail to close the file!\n");
    }
    return EXIT_SUCCESS;
}