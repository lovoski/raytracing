#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <functional>
#include <iostream>
#include <string>
#include <chrono>
#include <cmath>

#include <imgui.h>
#include <imgui-SFML.h>

#include <Eigen/Core>

class framebuffer {
  private:
    sf::Image image;
    unsigned int width;
    unsigned int height;
    double clamp(double x) {
      x = x<0.0?0.0:x;
      x = x>1.0?1.0:x;
      return x;
    }
    double linear2gamma(double linear) {return sqrt(linear);}
  public:
    framebuffer(unsigned int _w = 1600, unsigned int _h = 900) : width(_w), height(_h) {
      image.create(_w, _h, sf::Color::Black);
    }
    ~framebuffer() {}
    void init(unsigned int _w, unsigned int _h) {
      width = _w;
      height = _h;
      image.create(width, height, sf::Color::Black);
    }
    unsigned int get_width() {return width;}
    unsigned int get_height() {return height;}
    sf::Image& get_image() {return image;}
    void save_image(std::string filename) {image.saveToFile(filename);}
    void set_pixel(unsigned int x, unsigned int y, Eigen::Vector3d &color) {
      image.setPixel(x, y, sf::Color(
        static_cast<sf::Uint8>(clamp(linear2gamma(color.x()))*255), 
        static_cast<sf::Uint8>(clamp(linear2gamma(color.y()))*255), 
        static_cast<sf::Uint8>(clamp(linear2gamma(color.z()))*255)));
    }
};

// Display framebuffer as fixed sized image, ESC to exit, S to save as "xxx.png"
void display_image(framebuffer &buffer) {
  const unsigned int width = buffer.get_width();
  const unsigned int height = buffer.get_height();
  sf::RenderWindow window(sf::VideoMode(width, height), "framebuffer viewer", sf::Style::Close | sf::Style::Titlebar);
  sf::Texture texture;
  texture.loadFromImage(buffer.get_image());
  sf::Sprite sprite(texture);
  window.clear();
  window.draw(sprite);
  window.display();
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape)
          window.close();
        else if (event.key.code == sf::Keyboard::S) {
          auto cur_time = std::chrono::system_clock::now();
          std::time_t cur_time_t = std::chrono::system_clock::to_time_t(cur_time);
          std::string img_filename = std::to_string(cur_time_t)+".png";
          buffer.save_image(img_filename);
          std::cout << "current rendering saved as:" << img_filename << std::endl;
        }
        else;
      }
    }
  }
}

class render_window {
private:
  std::function<void(sf::Event &event)> 
  m_event_handler = [&](sf::Event &event) {};

  sf::Clock m_clock;
public:
  unsigned int width;
  unsigned int height;
  sf::RenderWindow *window;
  framebuffer buffer;
  render_window(const unsigned int _width = 1600, const unsigned int _height = 900, const char *title = "render window")
  : width(_width), height(_height) {
    window = new sf::RenderWindow(sf::VideoMode(_width, _height), title, sf::Style::Close | sf::Style::Titlebar);
    buffer.init(_width, _height);
    ImGui::SFML::Init(*window);
  }
  ~render_window() {
    ImGui::SFML::Shutdown();
    delete window;
  }
  // The render function takes four parameters, framebuffer, width, height and delta time as seconds
  void render_loop(std::function<void(framebuffer&, unsigned int, unsigned int, double)> render_func) {
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
      // get delta time
      dt = m_clock.restart();
      // update imgui
      ImGui::SFML::Update(*window, dt);
      // modify the framebuffer
      render_func(buffer, width, height, dt.asSeconds());
      sf::Texture texture;
      texture.loadFromImage(buffer.get_image());
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