#pragma once
#include "renderer.h"
#include "../elements/game_world.h"

class ConsoleRenderer : Renderer {
public:
  void draw(const std::unique_ptr<GameWorld>& world);
};