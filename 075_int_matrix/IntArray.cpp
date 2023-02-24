#include "IntArray.h"
#include <assert.h>
#include <ostream>

IntArray::IntArray() : data(NULL), numElements(0)
{
}
IntArray::IntArray(int n) : data(new int[n]), numElements(n)
{
}

IntArray::IntArray(const IntArray &rhs)
    : data(new int[rhs.numElements]), numElements(rhs.numElements)
{
    for (int i = 0; i < numElements; i++)
    {
        data[i] = rhs.data[i];
    }
}
IntArray::~IntArray()
{
    delete[] data;
}

IntArray &IntArray::operator=(const IntArray &rhs)
{
    if (this != &rhs)
    {
        delete[] data;
        numElements = rhs.numElements;
        data = new int[rhs.numElements];
        for (int i = 0; i < numElements; i++)
        {
            data[i] = rhs.data[i];
        }
    }
    return *this;
}
const int &IntArray::operator[](int index) const
{
    return data[index];
}
int &IntArray::operator[](int index)
{
    return data[index];
}

int IntArray::size() const
{
    return numElements;
}

bool IntArray::operator==(const IntArray &rhs) const
{
    if (numElements != rhs.numElements)
    {
        return false;
    }
    for (int i = 0; i < numElements; i++)
    {
        if (data[i] != rhs.data[i])
        {
            return false;
        }
    }
    return true;
}

bool IntArray::operator!=(const IntArray &rhs) const
{
    if (numElements != rhs.numElements)
    {
        return true;
    }
    for (int i = 0; i < numElements; i++)
    {
        if (data[i] != rhs.data[i])
        {
            return true;
        }
    }
    return false;
}

std::ostream &operator<<(std::ostream &s, const IntArray &rhs)
{
    s << "{";
    for (int i = 0; i < rhs.size() - 1; i++)
    {
        s << rhs[i] << ", ";
    }
    if (rhs.size() != 0)
    {
        s << rhs[rhs.size() - 1] << "}";
    }
    else
    {
        s << "}";
    }
    return s;
}
