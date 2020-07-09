#pragma once
#include <string>
#include <vector>

class GameWorld {
public:
  GameWorld();
  ~GameWorld();

  void setup();

  std::vector<std::vector<bool>> level_map;
private:
  void read_level_map(std::string level_file);
};