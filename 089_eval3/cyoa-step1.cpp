#include "Page.hpp"
#include "tools.hpp"

int main(int argc, char **argv) {
    // throw error when arguments number is not enough
    if (argc != 2) {
        printErrorAndExit("Usage: ./cyoa-step1 {pagePath}");
    }

    Page page(argv[1], 1);
    page.printSinglePage();
    return EXIT_SUCCESS;
}