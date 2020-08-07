#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../input.h"

class GameWorld {
public:
  GameWorld();
  ~GameWorld();

  void setup();
  void update(const std::unique_ptr<Input>& input);
  void loop();

  std::vector<std::vector<bool>> level_map;
private:
  void read_level_map(std::string level_file);
};