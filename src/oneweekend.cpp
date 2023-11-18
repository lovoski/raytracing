#include "gui.hpp"
#include "ray.hpp"
#include "global.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "material.hpp"

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

int main() {
  // materials
  auto mat_ground = make_shared<lambertian>(vec3(0.8, 0.8, 0));
  auto mat_sphere = make_shared<lambertian>(vec3(0.9, 0.3, 0.3));
  auto mat_left = make_shared<transparent>(1.5);
  auto mat_right = make_shared<metal>(vec3(0.8, 0.6, 0.2), 0);

  // objects
  hittable_list world;
  world.add(make_shared<sphere>(sphere(0.5, vec3(0.0, 0.0, -1.0), mat_sphere)));
  world.add(make_shared<sphere>(sphere(100.0, vec3(0.0, -100.5, -1.0), mat_ground)));
  world.add(make_shared<sphere>(sphere(0.5, vec3(-1.0, 0.0, -1.0), mat_left)));
  world.add(make_shared<sphere>(sphere(-0.4, vec3(-1.0, 0.0, -1.0), mat_left)));
  world.add(make_shared<sphere>(sphere(0.5, vec3( 1.0, 0.0, -1.0), mat_right)));

  // camera
  camera cam(SCREEN_WIDTH, SCREEN_HEIGHT, deg2rad(100.0));

  cam.samples_per_pixel = 30;
  cam.max_depth = 30;

  // display rendering
  display_image(cam.render(world));
  return 0;
}