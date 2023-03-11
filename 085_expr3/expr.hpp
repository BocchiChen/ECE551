#include <cstdlib>
#include <iostream>
#include <sstream>

class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual long evaluate() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
  long number;

 public:
  NumExpression(long n) : number(n) {}
  virtual std::string toString() const {
    std::stringstream ret;
    ret << number;
    return ret.str();
  }
  long evaluate() const { return number; }
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
  long evaluate() const { return lhs->evaluate() + rhs->evaluate(); }
  ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
};
class MinusExpression : public Expression {
  Expression * lhs;
  Expression * rhs;

 public:
  MinusExpression(Expression * lhs, Expression * rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
  }
  std::string toString() const {
    std::stringstream ret;
    ret << "(" << lhs->toString() << " - " << rhs->toString() << ")";
    return ret.str();
  }
  long evaluate() const { return lhs->evaluate() - rhs->evaluate(); }
  ~MinusExpression() {
    delete lhs;
    delete rhs;
  }
};
class TimesExpression : public Expression {
  Expression * lhs;
  Expression * rhs;

 public:
  TimesExpression(Expression * lhs, Expression * rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
  }
  std::string toString() const {
    std::stringstream ret;
    ret << "(" << lhs->toString() << " * " << rhs->toString() << ")";
    return ret.str();
  }
  long evaluate() const { return lhs->evaluate() * rhs->evaluate(); }
  ~TimesExpression() {
    delete lhs;
    delete rhs;
  }
};
class DivExpression : public Expression {
  Expression * lhs;
  Expression * rhs;

 public:
  DivExpression(Expression * lhs, Expression * rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
  }
  std::string toString() const {
    std::stringstream ret;
    ret << "(" << lhs->toString() << " / " << rhs->toString() << ")";
    return ret.str();
  }
  long evaluate() const { return lhs->evaluate() / rhs->evaluate(); }
  ~DivExpression() {
    delete lhs;
    delete rhs;
  }
};
