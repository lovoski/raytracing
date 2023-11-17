#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "global.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"

class camera {
private:
  double fov; // fov of y-axis
  unsigned int width;
  unsigned int height;
  double aspect_ratio;
  vec3 cam_pos;
public:
  camera(unsigned int _width, unsigned int _height, double _fov, vec3 _pos)
  : width(_width), height(_height), fov(_fov), cam_pos(_pos) {
    aspect_ratio = _width/_height;
  }
  ~camera() {}

  sf::Color ray_color(ray &r, hittable_list &world) {
    hit_record rec;
    vec3 color;
    if (world.hit(r, interval(0, infinity), rec)) {
      color = (rec.normal+vec3(1.0, 1.0, 1.0))*0.5*255;
    } else {
      color = r.d.normalized()*255;
    }
    return sf::Color(
      static_cast<sf::Uint8>(std::abs(color.x())),
      static_cast<sf::Uint8>(std::abs(color.y())),
      static_cast<sf::Uint8>(std::abs(color.z())));
  }

  sf::Image render(hittable_list &world) {
    sf::Image framebuffer;
    framebuffer.create(width, height, sf::Color::Black);
    for (int x = 0; x < width; ++x) {
      for (int y = 0; y < height; ++y) {
        // for each pixel
        vec3 pixel_pos(x-width/2.0, height/2.0-y, -0.5*height/std::tan(fov/2.0));
        ray r(cam_pos, (pixel_pos-cam_pos).normalized());
        framebuffer.setPixel(x, y, ray_color(r, world));
      }
    }
    return framebuffer;
  }
};

#endif