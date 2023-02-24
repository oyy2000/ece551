#include "rand_story.h"

/**
 * @brief Init the used words category type
 *
 * @return category_t*
 */
category_t *initUsedWords() {
    category_t *usedWords = malloc(sizeof(*usedWords));
    checkMemory(usedWords);
    usedWords->name = malloc(sizeof(*usedWords->name));
    checkMemory(usedWords);
    usedWords->n_words = 0;
    usedWords->words = NULL;
    return usedWords;
}

/**
 * @brief Free certain category type
 * @param category is the category struct to be freed.
 */
void freeCat(category_t *category) {
    for (size_t i = 0; i < category->n_words; i++) {
        free(category->words[i]);
    }
    free(category->words);
    free(category->name);
}

/**
 * @brief Free certain catarray type.
 * @param catArr is the catarray struct to be freed.
 */
void freeCatArr(catarray_t *catArr) {
    for (size_t i = 0; i < catArr->n; i++) {
        freeCat(&catArr->arr[i]);
    }
    free(catArr->arr);
    free(catArr);
}

/**
 * @brief Check memory if is correctly allocated, if not print an error
 * @param malloced is the malloced space need to check if is correctly allocated.
 */
void checkMemory(void *malloced) {
    if (malloced == NULL) {
        printErrorAndExit("malloc/realloc failed!\n");
    }
}

/**
 * @brief Print an Error and exit with EXIT_FAILURE
 * @param errMsg is the error message
 */
void printErrorAndExit(const char *errMsg) {
    fprintf(stderr, "%s", errMsg);
    exit(EXIT_FAILURE);
}

/**
 * @brief Check whether the content of a blank is category or number
 *
 * @param catArr is the catarray struct
 * @param blank is the blank content to be check
 * @param usedWords is the category of used words
 * @param mode is the -n param
 * @param f is words file
 * @param f2 is story file
 * @param idxes is index array of two underscores
 * @param line is the original line of file
 * @param strBefore_ is the pointer of string before the blank
 * @param strAfter_ is the pointer of string after the blank
 * @return long
 */
long isBlankNum(catarray_t *catArr,
                char *blank,
                category_t *usedWords,
                int mode,
                FILE *f,
                FILE *f2,
                size_t *idxes,
                char *line, char *strBefore_, char *strAfter_) {
    long num = strtol(blank, NULL, 10);
    // according to the step2 README, _-1_ _0_ _2asdb_ are not inherently invalid.
    if (num <= 0) {
        return 0;
    }
    if (errno == ERANGE) {
        // free all when encounter problems
        freeCat(usedWords);
        free(usedWords);
        freeCatArr(catArr);
        free(blank);
        free(idxes);
        free(line);
        free(strBefore_);
        free(strAfter_);
        if (fclose(f) != 0) {
            printErrorAndExit("Fail to close the file!\n");
        }
        if (fclose(f2) != 0) {
            printErrorAndExit("Fail to close the file!\n");
        }
        printErrorAndExit("Blank contains number out of ERANGE!\n");
    }
    return num;
}

/**
 * @brief Get the two indexes of a pair of underscore
 *
 * @param line is the original line of file
 * @param f is story file
 * @param usedWords is the category of used words
 * @return size_t*
 */
size_t *getIdxesOf_(char *line, FILE *f, category_t *usedWords) {
    char *ptrOf_1 = strchr(line, '_');
    char *ptrOf_2 = NULL;
    if (ptrOf_1 == NULL) {
        // constrain to return NULL if there is no first _
        return NULL;
    } else {
        if (ptrOf_1 - line + 1 < strlen(line)) {
            // from the char after first _ to search for another _
            ptrOf_2 = strchr(ptrOf_1 + 1, '_');
        }
        if (ptrOf_2 == NULL) {
            // free all when encounter problems
            freeCat(usedWords);
            free(usedWords);
            free(line);
            if (fclose(f) != 0) {
                printErrorAndExit("Fail to close the file!\n");
            }
            printErrorAndExit("Find single '_' which is not valid.\n");
        }
        // store the index of two _ and return
        size_t *idxes = malloc(2 * sizeof(*idxes));
        checkMemory(idxes);

        idxes[0] = ptrOf_1 - line;
        idxes[1] = ptrOf_2 - line;
        return idxes;
    }
}

/**
 * @brief Extract the content of blank with the indexes of two underscores
 *
 * @param line is the original line of file
 * @param idxes is index array of two underscores
 * @return char*
 */
char *extractBlank(const char *line, size_t *idxes) {
    size_t idxOf_1 = idxes[0];
    size_t idxOf_2 = idxes[1];
    size_t length = idxOf_2 - idxOf_1;
    char *blank = malloc(length * sizeof(*blank));
    checkMemory(blank);
    // copying blank from original line
    for (size_t i = 0; i < length - 1; i++) {
        blank[i] = line[idxOf_1 + i + 1];
    }
    blank[length - 1] = '\0';
    return blank;
}

/**
 * @brief return the duplication of choose word
 *
 * @param catArr is the catarray struct
 * @param blank is the blank content to be check
 * @param usedWords is the category of used words
 * @param mode is the -n param
 * @param f is words file
 * @param f2 is story file
 * @param idxes is index array of two underscores
 * @param line is the original line of file
 * @param strBefore_ is the pointer of string before the blank
 * @param strAfter_ is the pointer of string after the blank
 * @return char*
 */
char *chooseWordDup(catarray_t *catArr, char *blank, category_t *usedWords,
                    int mode, FILE *f, FILE *f2, size_t *idxes, char *line, char *strBefore_, char *strAfter_) {
    if (catArr == NULL) {
        const char *word = chooseWord(blank, catArr);
        if (word == NULL) {
            printErrorAndExit("Word should not be NULL\n");
        }
        return strdup(word);
    } else { // try to parse the blank into num
        long num = isBlankNum(catArr, blank, usedWords, mode, f, f2, idxes, line, strBefore_, strAfter_);
        if (num == 0) // if blank is a category, get the category word
        {
            return strdup(getCatWord(catArr, blank, usedWords, mode, f, f2, idxes, line, strBefore_, strAfter_));
        } else // if blank is an integer, get the used word
        {
            return strdup(getUsedWord(num, usedWords, catArr, blank, f, f2, idxes, line, strBefore_, strAfter_));
        }
    }
}

/**
 * @brief Convert the original line of story file into the parsed one
 *
 * @param line is the original line of file
 * @param idxes is index array of two underscores
 * @param catArr is the catarray struct
 * @param usedWords is the category of used words
 * @param mode is the -n param
 * @param f is words file
 * @param f2 is story file
 * @return char*
 */
char *parseLine(char *line, size_t *idxes, catarray_t *catArr, category_t *usedWords, int mode, FILE *f, FILE *f2) {
    char *strBefore_ = strndup(line, idxes[0]);
    char *strAfter_ = strndup(line + idxes[1] + 1, strlen(line) - (idxes[1] + 1));
    char *blank = extractBlank(line, idxes); // need to be freed
    char *wordDup = chooseWordDup(catArr, blank, usedWords, mode, f, f2, idxes, line, strBefore_, strAfter_);
    // allocate the space of line
    free(line);
    line = malloc((strlen(strBefore_) + strlen(wordDup) + strlen(strAfter_) + 1) * sizeof(*line));
    line[0] = '\0';

    // join the line
    strcat(line, strBefore_);
    strcat(line, wordDup);
    strcat(line, strAfter_);

    // free all
    free(wordDup);
    free(strBefore_);
    free(strAfter_);
    free(blank);
    return line;
}

/**
 * @brief Convert the whole story into the parsed one
 *
 * @param f2 is words file
 * @param f is story file
 * @param catArr is the catarray struct
 * @param mode is the -n param
 */
void parseStory(FILE *f2, FILE *f, catarray_t *catArr, int mode) {
    char *line = NULL;
    size_t *idxes = NULL;

    size_t size;
    category_t *usedWords = initUsedWords();
    while (getline(&line, &size, f) >= 0) {
        // check all the _ pairs
        while ((idxes = getIdxesOf_(line, f, usedWords)) != NULL) {
            line = parseLine(line, idxes, catArr, usedWords, mode, f, f2);
            free(idxes);
        }
        free(idxes);
        fprintf(stdout, "%s", line);
        free(line);
        line = NULL;
    }

    // free all
    free(line);
    freeCat(usedWords);
    free(usedWords);
}

/**
 * @brief Add new category to catarray
 * @param catArr is the catarray struct
 * @param cat is the category added
 * @return category_t*
 */
category_t *addCat(catarray_t *catArr, char *cat) {
    catArr->arr = realloc(catArr->arr, (catArr->n + 1) * sizeof(*catArr->arr));
    checkMemory(catArr->arr);
    catArr->n += 1;
    category_t *category = &catArr->arr[catArr->n - 1];
    // init category
    category->name = cat;
    category->n_words = 0;
    category->words = NULL;
    return category;
}

/**
 * @brief Get the certain category
 *
 * @param catArr is the catarray struct
 * @param cat is the category added
 * @return category_t*
 */
category_t *getCat(const catarray_t *catArr, const char *cat) {
    for (size_t i = 0; i < catArr->n; i++) {
        // if the name of one category is the same as the param, then return it.
        if (!strcmp(catArr->arr[i].name, cat)) {
            return &catArr->arr[i];
        }
    }
    // if nothing compare, return NULL instead for check
    return NULL;
}

/**
 * @brief Parse the string after ":"
 *
 * @param line is the original line of file
 * @param i is the pointer of one index in line
 * @param f is words file
 * @param catArr is the catarray struct
 * @param cat is the string of cat
 * @param closeFile is story file
 * @return char*
 */
char *parseWord(char *line, size_t *i, FILE *f, catarray_t *catArr,
                char *cat, FILE *closeFile) {
    char *word = malloc((strlen(line) + 1) * sizeof(*word));
    checkMemory(word);
    size_t j = *i + 1;
    while (j < strlen(line) && line[j] != '\n') {
        word[j - *i - 1] = line[j];
        j++;
    }
    if (j >= strlen(line)) {
        // free all when encounter problems
        free(word);
        free(cat);
        free(line);
        freeCatArr(catArr);
        if (fclose(f) != 0) {
            printErrorAndExit("Fail to close the file!\n");
        }
        if (fclose(closeFile) != 0) {
            printErrorAndExit("Fail to close the file!\n");
        }
        printErrorAndExit("Word does not contain \\n\n");
    }
    word[j - *i - 1] = '\0';
    return word;
}

/**
 * @brief Parse the string before ":"
 *
 * @param line is the original line of file
 * @param i is the pointer of one index in line
 * @param f is words file
 * @param catArr is the catarray struct
 * @return char*
 */
char *parseCat(char *line, size_t *i, FILE *f, catarray_t *catArr) {
    char *cat = malloc((strlen(line) + 1) * sizeof(*cat));
    checkMemory(cat);
    while (*i < strlen(line) && line[*i] != ':') {
        cat[*i] = line[*i];
        (*i)++;
    }
    // if word does not contain ':', print error
    if (line[*i] != ':') {
        // free all
        free(cat);
        free(line);
        freeCatArr(catArr);
        if (fclose(f) != 0) {
            printErrorAndExit("Fail to close the file!\n");
        }
        printErrorAndExit("Word does not contain ':' \n");
    }
    cat[*i] = '\0';
    return cat;
}

/**
 * @brief Add a new word to a category.
 * @param category - The category will be added.
 * @param word - The word need adding.
 */
void addWord(category_t *category, char *word) {
    category->words = realloc(category->words, (category->n_words + 1) * sizeof(*category->words));
    checkMemory(category->words);
    category->n_words += 1;
    category->words[category->n_words - 1] = word;
}

/**
 * @brief Parse the words file
 *
 * @param f is words file
 * @param closeFile is story file
 * @return catarray_t*
 */
catarray_t *parseWords(FILE *f, FILE *closeFile) {
    char *line = NULL;
    size_t size;
    // init the catarray
    catarray_t *catArr = malloc(sizeof(*catArr));
    checkMemory(catArr);
    catArr->n = 0;
    catArr->arr = NULL;
    while (getline(&line, &size, f) >= 0) {
        size_t index = 0;
        // parse the string before and after ":"
        char *cat = parseCat(line, &index, f, catArr);
        char *word = parseWord(line, &index, f, catArr, cat, closeFile);
        category_t *category = getCat(catArr, cat);
        if (category != NULL) {
            free(cat);
        } else {
            // stores the category names
            category = addCat(catArr, cat);
        }
        addWord(category, word);
    }
    free(line);
    line = NULL;
    return catArr;
}

/**
 * @brief Get one word from the used category
 *
 * @param catArr is the catarray struct
 * @param blank is the blank content to be check
 * @param usedWords is the category of used words
 * @param mode is the -n param
 * @param f is words file
 * @param f2 is story file
 * @param idxes is index array of two underscores
 * @param line is the original line of file
 * @param strBefore_ is the pointer of string before the blank
 * @param strAfter_ is the pointer of string after the blank
 * @return char*
 */
char *getUsedWord(long num, category_t *usedWords, catarray_t *catArr,
                  char *blank, FILE *f, FILE *f2, size_t *idxes,
                  char *line, char *strBefore_, char *strAfter_) {
    if (num > usedWords->n_words) {
        // free all when encounter problems
        freeCat(usedWords);
        free(usedWords);
        freeCatArr(catArr);
        free(blank);
        free(idxes);
        free(line);
        free(strBefore_);
        free(strAfter_);
        if (fclose(f) != 0) {
            printErrorAndExit("Fail to close the file!\n");
        }
        if (fclose(f2) != 0) {
            printErrorAndExit("Fail to close the file!\n");
        }
        printErrorAndExit("Blank contains number bigger than the number of used words!\n");
    }
    char *word = strdup(usedWords->words[usedWords->n_words - num]);
    addWord(usedWords, word);
    return word;
}

/**
 * @brief Get the one word from a certain category
 *
 * @param catArr is the catarray struct
 * @param blank is the blank content to be check
 * @param usedWords is the category of used words
 * @param mode is the -n param
 * @param f is words file
 * @param f2 is story file
 * @param idxes is index array of two underscores
 * @param line is the original line of file
 * @param strBefore_ is the pointer of string before the blank
 * @param strAfter_ is the pointer of string after the blank
 * @return char*
 */
char *getCatWord(catarray_t *catArr, char *blank, category_t *usedWords,
                 int mode, FILE *f, FILE *f2, size_t *idxes, char *line,
                 char *strBefore_, char *strAfter_) {
    category_t *category = getCat(catArr, blank);
    if (category == NULL) {
        // free all when encounter problems
        freeCat(usedWords);
        free(usedWords);
        freeCatArr(catArr);
        free(blank);
        free(idxes);
        free(line);
        free(strBefore_);
        free(strAfter_);
        if (fclose(f) != 0) {
            printErrorAndExit("Fail to close the file!\n");
        }
        if (fclose(f2) != 0) {
            printErrorAndExit("Fail to close the file!\n");
        }
        printErrorAndExit("Story template contains invalid category name!\n");
    }
    if (category->n_words <= 0) {
        // free all when encounter problems
        freeCat(usedWords);
        free(usedWords);
        freeCatArr(catArr);
        free(blank);
        free(idxes);
        free(line);
        free(strBefore_);
        free(strAfter_);
        if (fclose(f) != 0) {
            printErrorAndExit("Fail to close the file!\n");
        }
        if (fclose(f2) != 0) {
            printErrorAndExit("Fail to close the file!\n");
        }
        printErrorAndExit("There is no more words in this category!\n");
    }
    char *word = strdup(chooseWord(blank, catArr));
    checkMemory(word);
    if (mode > 0) {
        removeWord(category, word);
    }
    addWord(usedWords, word);
    return word;
}

/**
 * @brief Remove one word from a category.
 *
 * @param category is the category_t struct that contains the word
 * @param word
 */
void removeWord(category_t *category, const char *word) {
    size_t i = 0;
    for (; i < category->n_words; i++) {
        if (strcmp(category->words[i], word) == 0) {
            // memorize the index of the word need to be remove
            break;
        }
    }
    free(category->words[i]);
    for (size_t j = i; j < category->n_words - 1; ++j) {
        category->words[j] = category->words[j + 1];
    }

    // narrow the space of category
    category->words = realloc(category->words, (category->n_words - 1) * sizeof(*category->words));
    category->n_words--;
}