#include "bstset.h"

int main()
{
    BstSet<int> Bs;
    Bs.add(5);
    Bs.add(6);
    Bs.add(7);
    Bs.add(8);
    Bs.add(9);

    Bs.remove(9);
    // cout<<Bs.contains(3);
    BstSet<int> Bs2 = Bs;
    Bs2 = Bs;
    return EXIT_SUCCESS;
}