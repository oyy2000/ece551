#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

// Tools
category_t *initUsedWords();
void freeCat(category_t *category);
void freeCatArr(catarray_t *catArr);
void checkMemory(void *malloced);
void printErrorAndExit(const char *errMsg);

// Parsing story
long isBlankNum(catarray_t *catArr,
                char *blank,
                category_t *usedWords,
                int mode,
                FILE *f,
                FILE *f2,
                size_t *idxes,
                char *line, char *strBefore_, char *strAfter_);
size_t *getIdxesOf_(char *line, FILE *f, category_t *usedWords);
char *extractBlank(const char *line, size_t *idxes);
char *chooseWordDup(catarray_t *catArr, char *blank, category_t *usedWords,
                    int mode, FILE *f, FILE *f2,
                    size_t *idxes, char *line,
                    char *strBefore_, char *strAfter_);
char *parseLine(char *line, size_t *idxes, catarray_t *catArr,
                category_t *usedWords, int mode, FILE *f, FILE *f2);
void parseStory(FILE *f2, FILE *f, catarray_t *catArr, int mode);

// Parsing Words
category_t *addCat(catarray_t *catArr, char *cat);
category_t *getCat(const catarray_t *catArr, const char *cat);
char *parseWord(char *line, size_t *i, FILE *f, catarray_t *catArr,
                char *cat, FILE *closeFile);
char *parseCat(char *line, size_t *i, FILE *f, catarray_t *catArr);
void addWord(category_t *category, char *word);
catarray_t *parseWords(FILE *f, FILE *closeFile);
char *getUsedWord(long num, category_t *usedWords, catarray_t *catArr,
                  char *blank, FILE *f, FILE *f2, size_t *idxes,
                  char *line, char *strBefore_, char *strAfter_);
char *getCatWord(catarray_t *catArr, char *blank, category_t *usedWords,
                 int mode, FILE *f, FILE *f2, size_t *idxes, char *line,
                 char *strBefore_, char *strAfter_);
void removeWord(category_t *category, const char *word);
#endif
