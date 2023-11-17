#ifndef INTERVAL_HPP
#define INTERVAL_HPP

#include <limits>

class interval {
public:
  double min, max;
  interval() {
    min = std::numeric_limits<double>::infinity();
    max = -min;
  }
  interval(double _min, double _max) : min(_min), max(_max) {}
  ~interval() {}

  bool in(double x) {return x>=min && x<=max;}
  bool out(double x) {return x<min || x>max;}
};

#endif