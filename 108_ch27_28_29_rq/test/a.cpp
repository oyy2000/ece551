#include <iostream>
#include <vector>

using namespace std;

class A
{
protected:
    std::string name;

public:
    explicit A(std::string str) : name(str) {}
    virtual void showType()
    {
        std::cout << "I am of type A" << std::endl;
    }
    void showName()
    {
        std::cout << "An object of type A named " << name << std::endl;
    }
};
class B : public A
{
public:
    explicit B(std::string str) : A(str){};
    virtual void showType()
    {
        std::cout << "I am of type B" << std::endl;
    }
    void showName()
    {
        std::cout << "An object of type B named " << name << std::endl;
    }
};

int main()
{
    // A a("objectA");
    // a.showType();
    // a.showName();

    A *b = new B("objectB");
    b->showType();
    b->showName();
}
