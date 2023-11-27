#include "window.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
int start_x = 0, end_x = 10, start_y = 0, end_y = 10;

int main() {
  render_window window(SCREEN_WIDTH, SCREEN_HEIGHT);

  // event handler
  window.set_event_handler([&](sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::Escape) {
        window.window->close();
      }
    }
  });

  auto render_func = [&](framebuffer &buffer, unsigned int width, unsigned int height, double dt) {
    buffer.init(width, height);
    ImGui::Begin("settings");
    ImGui::SliderInt("start_x", &start_x, 0, end_x, "start_x=%d");
    ImGui::SliderInt("end_x", &end_x, start_x, SCREEN_WIDTH, "end_x=%d");
    ImGui::SliderInt("start_y", &start_y, 0, end_y, "start_y=%d");
    ImGui::SliderInt("end_y", &end_y, start_y, SCREEN_HEIGHT, "end_y=%d");
    ImGui::Text("frame rate=%.2f", 1.0f/(dt/1000000.0f));
    ImGui::End();

    for (int x = start_x; x < end_x; ++x) {
      for (int y = start_y; y < end_y; ++y) {
        buffer.set_pixel(x, y, vec3(1.0, 1.0, 1.0));
      }
    }
  };

  // update framebuffer and imgui
  window.render_loop(render_func);

  return 0;
}
