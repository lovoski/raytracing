#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <cmath>
#include <limits>
#include <memory>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <random>

// Common headers
#include "ray.hpp"
#include "interval.hpp"
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Sparse>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;
using vec2 = Eigen::Vector2d;
using vec3 = Eigen::Vector3d;
using vec4 = Eigen::Vector4d;
using mat3 = Eigen::Matrix3d;
using mat4 = Eigen::Matrix4d;

const double eps = 0.00001;
const double pi = 3.1415926535;
const double infinity = std::numeric_limits<double>::infinity();

inline std::mt19937& rand_generator() {
  static std::random_device rd;
  static std::mt19937 rng(rd());
  return rng;
}
constexpr double deg2rad(double deg) {return pi*deg/180.0;}
double rand_double() {
  std::uniform_real_distribution<double> dist(0, 1);
  return dist(rand_generator());
}
double rand_double(double min, double max) {
  std::uniform_real_distribution<double> dist(min, max);
  return dist(rand_generator());
}
vec3 rand_vec3_on_unit_sphere(){
  vec3 p;
  static std::default_random_engine generator{std::random_device{}()};
  std::uniform_real_distribution<float> distribution(0.0, 1.0);
  do {
    p = 2.0*vec3(distribution(generator),distribution(generator),distribution(generator)) - vec3(1,1,1);
  } while (p.norm() >= 1.0);
  return p.normalized();
}
vec3 rand_vec3_on_hemisphere(vec3 &normal) {
  vec3 ret = rand_vec3_on_unit_sphere();
  if (ret.dot(normal) > 0) return ret;
  else return -ret;
}
// gamma correction
inline double linear2gamma(double linear) {return sqrt(linear);}
// from [0, 1] to [0, 255]
sf::Color format_color(vec3 &color) {
  static const interval intensity(0.0, 1.0);
  color(0) = linear2gamma(color(0));
  color(1) = linear2gamma(color(1));
  color(2) = linear2gamma(color(2));
  return sf::Color(
    static_cast<sf::Uint8>(intensity.clamp(color.x())*255),
    static_cast<sf::Uint8>(intensity.clamp(color.y())*255),
    static_cast<sf::Uint8>(intensity.clamp(color.z())*255)
  );
}
vec3 reflect(vec3 &v, vec3 &n) {return v-2*v.dot(n)*n;}
vec3 cartesian(vec3 v, vec3 u) {return vec3(v.x()*u.x(), v.y()*u.y(), v.z()*u.z());}

#endif