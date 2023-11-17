#ifndef HITTABLE_LIST_HPP
#define HITTABLE_LIST_HPP

#include "hittable.hpp"

class hittable_list : public hittable {
public:
  std::vector<shared_ptr<hittable>> objects;
  hittable_list() {}
  ~hittable_list() {}

  void add(shared_ptr<hittable> object) {
    objects.push_back(object);
  }
  void clear() {
    objects.clear();
  }

  bool hit(ray &r, double r_tmin, double r_tmax, hit_record &rec) const override {
    hit_record m_rec;
    bool hit_something = false;
    double closest_t = r_tmax;
    for (auto &&object : objects) {
      if (object->hit(r, r_tmin, closest_t, m_rec)) {
        hit_something = true;
        closest_t = m_rec.t;
        rec = m_rec;
      }
    }
    return hit_something;
  }
};

#endif