#include "bstmap.h"
#include <string>
int main()
{
    BstMap<std::string, int> bstMap;
    bstMap.add("a", 1);
    bstMap.add("b", 2);
    bstMap.add("c", 3);
    bstMap.add("d", 4);
    bstMap.add("e", 5);

    bstMap.print(bstMap.getRoot());
    cout << endl;
    bstMap.remove("a");
    bstMap.print(bstMap.getRoot());
    cout << endl;
    bstMap.remove("ll");
    bstMap.print(bstMap.getRoot());
    cout << endl;
    bstMap.remove("c");
    bstMap.print(bstMap.getRoot());
    cout << endl;
    bstMap.remove("a");
    bstMap.print(bstMap.getRoot());
    return 0;
}