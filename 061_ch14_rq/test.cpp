#include <iostream>
using namespace std;
void doSomething(const int *const x)
{
    cout << *x << endl;
}
int main()
{
    // const int temp = 3;
    doSomething(&3);
}