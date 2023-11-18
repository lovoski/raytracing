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
  // objects
  hittable_list world;
  world.add(make_shared<sphere>(sphere(0.5, vec3(0.0, 0.0, -1.0))));
  world.add(make_shared<sphere>(sphere(100.0, vec3(0.0, -100.5, -1.0))));

  // camera
  camera cam(SCREEN_WIDTH, SCREEN_HEIGHT, deg2rad(90.0));

  display_image(cam.render(world));
  return 0;
}