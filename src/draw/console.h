#pragma once
#include "renderer.h"
#include "../elements/game_world.h"

class ConsoleRenderer : Renderer
{
public:
  ConsoleRenderer();
  ~ConsoleRenderer();

  void draw(const std::unique_ptr<GameWorld> &world);
  void stop();

private:
  bool _running;
};