cmake_minimum_required(VERSION 3.20)

project(raytracing-test)

include_directories(
  ${CMAKE_SOURCE_DIR}/includes)

add_executable(implement_test ${PROJECT_SOURCE_DIR}/implement_test.cpp)
add_executable(window_test ${PROJECT_SOURCE_DIR}/window_test.cpp)

target_link_libraries(
  implement_test
  PRIVATE
  ${LIBS})

target_link_libraries(
  window_test
  PRIVATE
  ${LIBS})
