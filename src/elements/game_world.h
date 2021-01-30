#pragma once
#include <functional>
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include "../input.h"

class GameWorld
{
public:
  GameWorld();
  ~GameWorld();

  void setup();
  void update(std::function<void(void)> update_fn);
  void update_input(const std::unique_ptr<Input> &input);
  void draw(std::function<void(void)> draw_fn);
  void loop();

  std::vector<std::vector<bool>> level_map;
  std::pair<int, int> cursor_position;

private:
  void read_level_map(std::string level_file);
  std::function<void(void)> _update_fn;
  std::function<void(void)> _draw_fn;
  bool _running;
};