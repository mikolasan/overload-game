#include "console.h"
#include <iostream>

void ConsoleRenderer::draw(const std::unique_ptr<GameWorld>& world) {
  auto map = world->level_map;
  for (auto line : map) {
    for (auto b : line) {
      std::cout << b ? "0" : ".";
    }
    std::cout << std::endl;
  }
}