#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "global.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"

class camera {
private:
  // from [0, 1] to [0, 255]
  sf::Color format_color(vec3 &color) {
    static const interval intensity(0.0, 0.9999);
    return sf::Color(
      static_cast<sf::Uint8>(intensity.clamp(color.x())*256),
      static_cast<sf::Uint8>(intensity.clamp(color.y())*256),
      static_cast<sf::Uint8>(intensity.clamp(color.z())*256)
    );
  }

public:
  double fov; // fov of y-axis
  unsigned int width;
  unsigned int height;
  double aspect_ratio;
  int samples_per_pixel = 10;
  vec3 bgcolor = vec3(1.0, 1.0, 1.0);
  vec3 cam_pos = vec3(0.0, 0.0, 0.0);

  camera(unsigned int _w, unsigned int _h, double _fov)
  : width(_w), height(_h), fov(_fov) {
    aspect_ratio = _w/_h;
  }
  ~camera() {}

  vec3 ray_trace(ray &r, hittable_list &world) {
    hit_record rec;
    vec3 color;
    if (world.hit(r, interval(0, infinity), rec)) {
      color = (rec.normal+vec3(1.0, 1.0, 1.0))*0.5;
    } else { // not hit, returns background color
      color = bgcolor;
    }
    return color;
  }

  sf::Image render(hittable_list &world) {
    sf::Image framebuffer;
    framebuffer.create(width, height, sf::Color::Black);
    for (int x = 0; x < width; ++x) {
      for (int y = 0; y < height; ++y) {
        // for each pixel
        vec3 pixel_color(0.0, 0.0, 0.0);
        // apply msaa
        for (int k = 0; k < samples_per_pixel; ++k) {
          vec3 pixel_pos(x-width/2.0+rand_double(), height/2.0-y-rand_double(), -0.5*height/std::tan(fov/2.0));
          ray r(cam_pos, (pixel_pos-cam_pos).normalized());
          pixel_color += ray_trace(r, world);
        }
        pixel_color /= samples_per_pixel;
        framebuffer.setPixel(x, y, format_color(pixel_color));
      }
    }
    return framebuffer;
  }
};

#endif