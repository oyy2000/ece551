#include <istream>
#include <string>
#include <sstream>
class Expression
{
public:
    virtual std::string toString() const = 0; // abstract method
    virtual ~Expression(){};
};

class NumExpression : public Expression
{
private:
    long _num;

public:
    NumExpression(long num) : _num(num){};
    virtual std::string toString() const
    {
        std::stringstream ss;
        ss << this->_num;
        return ss.str();
    }
    virtual ~NumExpression(){};
};

class PlusExpression : public Expression
{
private:
    Expression *lhs;
    Expression *rhs;

public:
    PlusExpression(Expression *lhs, Expression *rhs) : lhs(lhs), rhs(rhs){};
    virtual std::string toString() const
    {
        std::stringstream ss;
        ss << "(" << this->lhs->toString() << " + " << this->rhs->toString() << ")";
        return ss.str();
    }
    virtual ~PlusExpression()
    {
        delete this->lhs;
        delete this->rhs;
    }
};