#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "global.hpp"
#include "hittable.hpp"

class sphere : public hittable {
public:
  double radius;
  vec3 o;

  sphere(const double _r, const vec3 _o)
  : radius(_r), o(_o) {}
  ~sphere() {}

  double sdf(vec3 p) {
    return (p-o).norm();
  }
  bool hit(ray &r, interval r_interval, hit_record &rec) const {
    double a = r.d.dot(r.d);
    double half_b = r.d.dot(r.o-o);
    double c = (r.o-o).dot(r.o-o)-radius*radius;
    double discriminant = half_b*half_b-a*c;
    double sqrt_d = sqrt(discriminant);
    if (discriminant < 0.0)
      return false;
    // returns the first hit point
    double root = (-half_b-sqrt_d)/a;
    if (r_interval.out(root)) {
      root = (-half_b+sqrt_d)/a;
      if (r_interval.out(root))
        return false;
    }
    rec.t = root;
    rec.p = r.at(rec.t);
    rec.set_face_normal(r, (rec.p-o).normalized());
    return true;
  }
};

#endif