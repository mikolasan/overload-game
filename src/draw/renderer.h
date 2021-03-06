#pragma once
#include <memory>

class GameWorld;

class Renderer
{
public:
  virtual void draw(const std::unique_ptr<GameWorld> &world) = 0;
  virtual void stop() = 0;
};