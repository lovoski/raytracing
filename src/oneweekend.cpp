#include "gui.hpp"
#include "ray.hpp"
#include "global.hpp"
#include "sphere.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"

#include <cmath>
#include <iostream>

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

sf::Color ray_color(ray &r, hittable_list &world) {
  hit_record rec;
  vec3 pos;
  if (world.hit(r, 0, infinity, rec)) {
    pos = (rec.normal+vec3(1.0, 1.0, 1.0))*0.5*255;
  } else {
    pos = r.d.normalized()*255;
  }
  return sf::Color(
    static_cast<sf::Uint8>(std::abs(pos.x())),
    static_cast<sf::Uint8>(std::abs(pos.y())),
    static_cast<sf::Uint8>(std::abs(pos.z())));
}

int main() {
  gui render_window(SCREEN_WIDTH, SCREEN_HEIGHT);

  // objects
  hittable_list world;
  world.add(make_shared<sphere>(sphere(1.0, vec3(0.0, 0.0, -2.0))));
  world.add(make_shared<sphere>(sphere(100.0, vec3(0.0, -101, -1.0))));

  // camera settings
  const double fov = deg2rad(90.0);
  vec3 camera_pos(0.0, 0.0, 0.0);

  render_window.display_image([&](sf::Image &framebuffer, unsigned int width, unsigned int height) {
    for (int x = 0; x < width; ++x) {
      for (int y = 0; y < height; ++y) {
        // for each pixel
        vec3 pixel_pos(x-width/2.0, height/2.0-y, -0.5*height/std::tan(fov/2.0));
        ray r(camera_pos, (pixel_pos-camera_pos).normalized());
        framebuffer.setPixel(x, y, ray_color(r, world));
      }
    }
  });
  return 0;
}