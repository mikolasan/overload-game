#pragma once

#include <map>
#include "../elements/chip.h"

namespace 
{
  const int n_start_chips = 2;
}

class Player
{
public:
  Player(int x, int y, int id) : _id(id), _total_n_chips(n_start_chips)
  {
    Chip chip{
      .x = x,
      .y = y,
      .player_id = id,
      .size = n_start_chips,
    };
    _chips[{x, y}] = chip;
  };
  ~Player() {};

  int get_n_chips(int x, int y) { return _chips[{x, y}].size; };
private:
  std::map<std::pair<int, int>, Chip> _chips;
  int _id;
  int _total_n_chips;
};