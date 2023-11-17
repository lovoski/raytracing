#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "global.hpp"

struct hit_record {
  double t;
  vec3 p;
  vec3 normal;
  bool front_face;
  void set_face_normal(ray &r, vec3 n) {
    front_face = r.d.dot(n) < 0.0;
    normal = front_face ? n : -n;
  }
};

class hittable {
public:
  virtual ~hittable() = default;
  virtual bool hit(ray &r, double r_tmin, double r_tmax, hit_record &rec) const = 0;
};

#endif