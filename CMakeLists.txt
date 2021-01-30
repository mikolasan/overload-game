cmake_minimum_required (VERSION 3.14)

project(overload VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
# add_executable(overload 
#   src/draw/scene.cpp
#   src/elements/base.cpp
#   src/elements/colonn.cpp
#   src/elements/package.cpp
#   src/logic/playgrnd.cpp
#   src/main.cpp)
add_subdirectory(thirdparty/PDCurses)
include_directories(thirdparty/PDCurses)

add_executable(overload
  src/draw/console.cpp
  src/elements/game_world.cpp
  src/overload.cpp
  src/input.cpp)

target_link_libraries(overload pdcurses)