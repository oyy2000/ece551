#include "function.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cassert>
class CountedIntFn : public Function<int, int>
{
protected:
    unsigned remaining;
    Function<int, int> *f;
    const char *mesg;

public:
    CountedIntFn(unsigned n, Function<int, int> *fn, const char *m) : remaining(n),
                                                                      f(fn),
                                                                      mesg(m) {}
    virtual int invoke(int arg)
    {
        if (remaining == 0)
        {
            fprintf(stderr, "Too many function invocations in %s\n", mesg);
            exit(EXIT_FAILURE);
        }
        remaining--;
        return f->invoke(arg);
    }
};
int binarySearchForZero(Function<int, int> *f, int low, int high);
void check(Function<int, int> *f,
           int low,
           int high,
           int expected_ans,
           const char *mesg)
{
    int n = 1;
    if (high > low)
        n = log2(high - low) + 1;

    CountedIntFn *wrap_func = new CountedIntFn(n, f, mesg);
    int ans = binarySearchForZero(wrap_func, low, high);
    assert(ans == expected_ans);
}

class LinearFunction : public Function<int, int>
{
public:
    virtual int invoke(int arg) { return arg; }
};

int main()
{
    LinearFunction *linear = new LinearFunction();
    check(linear, -1, 4, 0, "t1");
    check(linear, -3, -1, -2, "t2");
    check(linear, 1, 4, 1, "t3");
    check(linear, 0, 1000, 0, "t4");
    check(linear, -4, 0, -1, "t5");
    return EXIT_SUCCESS;
}