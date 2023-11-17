#include "gui.hpp"
#include "ray.hpp"
#include "global.hpp"
#include "sphere.hpp"

#include <cmath>
#include <iostream>

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

sf::Color ray_color(ray r) {
  auto pos = r.d.normalized()*255;
  return sf::Color(
    static_cast<sf::Uint8>(std::abs(pos.x())),
    static_cast<sf::Uint8>(std::abs(pos.y())),
    static_cast<sf::Uint8>(std::abs(pos.z())));
}
sf::Color to_color(Eigen::Vector3d vec) {
  auto pos = vec.normalized()*255;
  return sf::Color(
    static_cast<sf::Uint8>(pos.x()),
    static_cast<sf::Uint8>(pos.y()),
    static_cast<sf::Uint8>(pos.z()));
}

int main() {
  gui render_window(SCREEN_WIDTH, SCREEN_HEIGHT);

  // objects
  sphere s1(1.0, Eigen::Vector3d(0.0, 0.0, -3.0));

  // camera settings
  const double fov = deg2rad(90.0);
  Eigen::Vector3d camera_pos(0.0, 0.0, 0.0);

  render_window.display_image([&](sf::Image &framebuffer, unsigned int width, unsigned int height) {
    for (int x = 0; x < width; ++x) {
      for (int y = 0; y < height; ++y) {
        // for each pixel
        Eigen::Vector3d pixel_pos(x-width/2.0, height/2.0-y, -0.5*height/std::tan(fov/2.0));
        ray r(camera_pos, (pixel_pos-camera_pos).normalized());
        double t =s1.hit(r);
        if (t != 0.0) {
          framebuffer.setPixel(x, y, to_color((r.at(t)-s1.o).normalized()+Eigen::Vector3d(1.0, 1.0, 1.0)));
        }
        else framebuffer.setPixel(x, y, ray_color(r));
      }
    }
  });
  return 0;
}