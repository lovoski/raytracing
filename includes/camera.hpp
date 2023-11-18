#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "global.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"

class camera {
private:
  // from [0, 1] to [0, 255]
  sf::Color format_color(vec3 &color) {
    static const interval intensity(0.0, 1.0);
    return sf::Color(
      static_cast<sf::Uint8>(intensity.clamp(color.x())*255),
      static_cast<sf::Uint8>(intensity.clamp(color.y())*255),
      static_cast<sf::Uint8>(intensity.clamp(color.z())*255)
    );
  }

public:
  double fov; // fov of y-axis
  unsigned int width;
  unsigned int height;
  double aspect_ratio;
  int max_depth = 10;
  int samples_per_pixel = 10;
  double r_tmin = 0.001;
  double r_tmax = infinity;
  vec3 cam_pos = vec3(0.0, 0.0, 0.0);

  camera(unsigned int _w, unsigned int _h, double _fov)
  : width(_w), height(_h), fov(_fov) {
    aspect_ratio = _w/_h;
  }
  ~camera() {}

  vec3 ray_trace(ray &r, hittable_list &world, int depth) {
    if (depth <= 0) return vec3(0, 0, 0);
    hit_record rec;
    if (world.hit(r, interval(r_tmin, r_tmax), rec)) {
      vec3 dir = rand_vec3_on_hemisphere(rec.normal).normalized();
      return 0.5*ray_trace(ray(rec.p, dir), world, depth-1);
    }
    double a = 0.7*(r.d.y()+1.0);
    return (1.0-a)*vec3(1.0, 1.0, 1.0)+a*vec3(0.5, 0.7, 1.0);
  }

  sf::Image render(hittable_list &world) {
    sf::Image framebuffer;
    framebuffer.create(width, height, sf::Color::Black);
    double viewplane_z = -0.5*height/std::tan(fov/2.0);
    for (int x = 0; x < width; ++x) {
      for (int y = 0; y < height; ++y) {
        // for each pixel
        vec3 pixel_color(0.0, 0.0, 0.0);
        // apply msaa
        for (int k = 0; k < samples_per_pixel; ++k) {
          vec3 pixel_pos(x-width/2.0+rand_double(), height/2.0-y-rand_double(), viewplane_z);
          ray r(cam_pos, (pixel_pos-cam_pos).normalized());
          pixel_color += ray_trace(r, world, max_depth);
        }
        pixel_color /= samples_per_pixel;
        framebuffer.setPixel(x, y, format_color(pixel_color));
      }
    }
    return framebuffer;
  }
};

#endif