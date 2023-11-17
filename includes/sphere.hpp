#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <Eigen/Core>

#include "ray.hpp"

class sphere {
public:
  double radius;
  Eigen::Vector3d o;

  sphere(const double _r, const Eigen::Vector3d _o)
  : radius(_r), o(_o) {}
  ~sphere() {}

  double sdf(Eigen::Vector3d p) {
    return (p-o).norm();
  }
  double hit(ray r) {
    double a = r.d.dot(r.d);
    double b = 2*r.d.dot(r.o-o);
    double c = (r.o-o).dot(r.o-o)-radius*radius;
    double discriminant = b*b-4*a*c;
    if (discriminant < 0.0)
      return 0.0;
    // returns the first hit point
    if ((r.at((-b-sqrt(discriminant))/(2.0*a))-o).dot(r.d) < 0.0) {
      return (-b-sqrt(discriminant))/(2.0*a);
    } else return (-b+sqrt(discriminant))/(2.0*a);
  }
};

#endif