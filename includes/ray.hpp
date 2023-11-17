#ifndef RAY_HPP
#define RAY_HPP

#include <Eigen/Core>

class ray {
public:
  Eigen::Vector3d o;
  Eigen::Vector3d d;

  ray() {}
  ray(const Eigen::Vector3d _o, const Eigen::Vector3d _d) 
  : o(_o), d(_d) {}
  ~ray() {}
  Eigen::Vector3d at(double t) {return o+t*d;}
};

#endif