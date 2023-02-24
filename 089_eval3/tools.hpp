#ifndef TOOL
#define TOOL

#include <string>
#include <iostream>
#include <cstdlib>
/**
 * @brief print Error And EXIT_FAILURE
 *
 * @param msg
 */
void printErrorAndExit(std::string msg) {
    std::cerr << msg << std::endl;
    exit(EXIT_FAILURE);
}

/**
 * @brief check if a string of choice num is valid number
 *
 * @param strChoiceNum
 * @return true
 * @return false
 */
bool isNumber(const std::string strChoiceNum) {
    for (size_t i = 0; i < strChoiceNum.length(); i++) {
        if (std::isdigit(strChoiceNum[i]) == false) {
            return false;
        }
    }
    return true;
}

#endif