#include <cstdlib>
#include <iostream>
#include <sstream>

class Expression {
  public:
    virtual std::string toString() const = 0;
    virtual ~Expression() {}
};

class NumExpression : public Expression{
  long number;
  public:
    NumExpression(long n) : number(n) {}
    virtual std::string toString() const{
      std::stringstream ret;
      ret << number;
      return ret.str();
    }
    virtual ~NumExpression() {}
};
class PlusExpression : public Expression {
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
  }
  std::string toString() const {
    std::stringstream ret;
    ret << "(" << lhs->toString() << " + " << rhs->toString() << ")";
    return ret.str();
  }
  ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
};