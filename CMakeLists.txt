cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)

project(raytracing)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

include_directories(
  ${CMAKE_SOURCE_DIR}/includes)

add_executable(window_test src/window_test.cpp)

target_link_libraries(
  window_test
  PRIVATE
  sfml-system
  sfml-network
  sfml-graphics
  sfml-window
  Eigen3::Eigen
  imgui::imgui
  ImGui-SFML::ImGui-SFML)