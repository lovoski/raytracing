#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <functional>

#include <imgui.h>
#include <imgui-SFML.h>

class gui {
private:
  std::function<void(sf::Event &event)> 
  m_event_handler = [&](sf::Event &event) {};

  sf::Clock m_clock;
public:
  unsigned int width;
  unsigned int height;
  sf::RenderWindow *window;
  sf::Image framebuffer;
  gui(const unsigned int _width = 1600, const unsigned int _height = 900, const char *title = "render window")
  : width(_width), height(_height) {
    window = new sf::RenderWindow(sf::VideoMode(_width, _height), title, sf::Style::Close | sf::Style::Titlebar);
    framebuffer.create(_width, _height);
    ImGui::SFML::Init(*window);
  }
  ~gui() {
    ImGui::SFML::Shutdown();
    delete window;
  }
  // The render function takes four parameters, framebuffer, width, height and delta time as microseconds
  void render_loop(std::function<void(sf::Image&, unsigned int, unsigned int, float)> render_func) {
    sf::Time dt;
    while (window->isOpen()) {
      sf::Event event;
      while (window->pollEvent(event)) {
        ImGui::SFML::ProcessEvent(event);
        if (event.type == sf::Event::Closed) {
          window->close();
        }
        m_event_handler(event);
      }
      // clear framebuffer
      framebuffer.create(width, height, sf::Color::Black);
      // get delta time
      dt = m_clock.restart();
      // update imgui
      ImGui::SFML::Update(*window, dt);
      // modify the framebuffer
      render_func(framebuffer, width, height, dt.asMicroseconds());
      sf::Texture texture;
      texture.loadFromImage(framebuffer);
      sf::Sprite sprite(texture);
      window->clear();
      window->draw(sprite);
      ImGui::SFML::Render(*window);
      window->display();
    }
  }
  void set_event_handler(std::function<void(sf::Event &event)> event_handler) {
    m_event_handler = event_handler;
  }
};

#endif