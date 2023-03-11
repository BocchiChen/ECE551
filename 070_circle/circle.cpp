#include "circle.hpp"
#include <cmath>

void Circle::move (double dx, double dy){
  this->center.move(dx,dy);
}

double Circle::intersectionArea(const Circle & otherCircle){
  double r1 = this->radius;
  double r2 = otherCircle.radius;
  double d = this->center.distanceFrom(otherCircle.center);
  if(d>=r1+r2){
    return 0;
  }
  if(r1>r2){
    double temp = r1;
    r1 = r2;
    r2 = temp;
  }
  if(r2-r1>=d){
    return acos(-1.0)*r1*r1;
  }
  double ang1 = acos((r1*r1+d*d-r2*r2)/(2*r1*d));
  double ang2 = acos((r2*r2+d*d-r1*r1)/(2*r2*d));
  return ang1*r1*r1 + ang2*r2*r2 - r1*d*sin(ang1);
}