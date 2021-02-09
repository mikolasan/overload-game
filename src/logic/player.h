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
    chips.insert({{x, y}, Chip(x, y, id, n_start_chips)});
  }
  ~Player(){}

  int get_n_chips(int x, int y) const { return chips.at({x, y}).size; }
  bool build_here(int x, int y, int k, std::function<void(int, int)> callback);
  // void explode(int x, int y);
  ControlType control_type;
  std::map<std::pair<int, int>, Chip> chips;
  int id;

private:
  int _total_n_chips;
};