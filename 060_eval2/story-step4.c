#include "rand_story.h"

/**
 * @brief If the argument "-n" is given, program should
 * ensure that chooseWord will not return a word that has
 * already been used.
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char **argv) {
    if (argc >= 5 || argc < 3) {
        printErrorAndExit("Usage: ./{prog_name} {-n|NULL} {words_txt_file_name} {story_txt_file_name}!!\n");
    }
    int mode = 0;
    FILE *f1 = NULL;
    FILE *f2 = NULL;
    if (argc == 4) {
        if (strcmp(argv[1], "-n")) {
            printErrorAndExit("Usage: ./{prog_name} {-n|NULL} {words_txt_file_name} {story_txt_file_name}!!\n");
        }
        mode = 1;
        f1 = fopen(argv[2], "r");
        if (f1 == NULL) {
            printErrorAndExit("Fail to open the file!\n");
        }
        f2 = fopen(argv[3], "r");
        if (f2 == NULL) {
            printErrorAndExit("Fail to open the file!\n");
        }
    } else {                      // mode = 0
        f1 = fopen(argv[1], "r"); // open the categories/words file
        if (f1 == NULL) {
            printErrorAndExit("Fail to open the file!\n");
        }
        f2 = fopen(argv[2], "r");
        if (f2 == NULL) {
            printErrorAndExit("Fail to open the file!\n");
        }
    }
    catarray_t *catArr = parseWords(f1, f2);
    parseStory(f1, f2, catArr, mode);
    freeCatArr(catArr);
    if (fclose(f1) != 0) {
        printErrorAndExit("Fail to close the file!\n");
    }
    if (fclose(f2) != 0) {
        printErrorAndExit("Fail to close the file!\n");
    }
    return EXIT_SUCCESS;
}