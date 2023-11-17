#include "gui.hpp"
#include "ray.hpp"
#include "global.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

int main() {
  gui render_window(SCREEN_WIDTH, SCREEN_HEIGHT);

  // objects
  hittable_list world;
  world.add(make_shared<sphere>(sphere(1.0, vec3(0.0, 0.0, -2.0))));
  world.add(make_shared<sphere>(sphere(100.0, vec3(0.0, -101, -1.0))));

  // camera settings
  camera cam(SCREEN_WIDTH, SCREEN_HEIGHT, deg2rad(90.0), vec3(0.0, 0.0, 0.0));

  render_window.display_image([&](sf::Image &framebuffer, unsigned int width, unsigned int height) {
    cam.render(framebuffer, width, height, world);
  });
  return 0;
}