#pragma once

#include <functional>
#include <map>
#include "../elements/chip.h"

namespace
{
  const int n_start_chips = 2;
}

class Player
{
public:
  enum class ControlType {
    HUMAN,
    AI,
  };
  Player(int x, int y, int id) : id(id), _total_n_chips(n_start_chips)
  {
    Chip chip{
        .x = x,
        .y = y,
        .player_id = id,
        .size = n_start_chips,
    };
    chips[{x, y}] = chip;
  }
  ~Player(){}

  int get_n_chips(int x, int y) { return chips[{x, y}].size; }
  bool build_here(int x, int y, int k, std::function<void(int, int)> callback);
  // void explode(int x, int y);
  ControlType control_type;
  std::map<std::pair<int, int>, Chip> chips;
  int id;

private:
  int _total_n_chips;
};