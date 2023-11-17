#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <cmath>
#include <limits>
#include <memory>
#include <vector>

// Common headers
#include "ray.hpp"
#include <Eigen/Core>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;
using vec3 = Eigen::Vector3d;

const double pi = 3.1415926535;
const double infinity = std::numeric_limits<double>::infinity();

constexpr double deg2rad(double deg) {return pi*deg/180.0;}

#endif