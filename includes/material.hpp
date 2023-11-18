#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "global.hpp"
#include "hittable.hpp"

// Abstract behavior for a material
class material {
public:
  virtual ~material() = default;
  virtual bool scatter(ray &r, hit_record &rec, vec3 &attennuation, ray &scattered) const = 0;
};

class lambertian : public material {
private:
  vec3 albedo;
public:
  lambertian(vec3 color) : albedo(color) {}
  bool scatter(ray &r, hit_record &rec, vec3 &attenuation, ray &scattered) const override {
    vec3 reflected_dir = rec.normal+rand_vec3_on_unit_sphere();
    if (reflected_dir.norm() < eps)
      scattered = ray(rec.p, rec.normal);
    else scattered = ray(rec.p, reflected_dir.normalized());
    attenuation = albedo;
    return true;
  }
};

class metal : public material {
private:
  vec3 albedo;
public:
  metal(vec3 color) : albedo(color) {}
  bool scatter(ray &r, hit_record &rec, vec3 &attenuation, ray &scattered) const override {
    scattered = ray(rec.p, reflect(r.d, rec.normal));
    attenuation = albedo;
    return true;
  }
};

#endif