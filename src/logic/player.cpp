#include "player.h"

bool Player::build_here(int x, int y, int k, std::function<void(int, int)> callback)
{
  _total_n_chips += k;
  auto& chip = chips[{x, y}];
  chip.size +=k;
  chip.player_id = id;
  if (chip.size >= 4) {
    callback(x, y);
  }
  return true;
}

// void Player::explode(int x, int y)
// {
  
// }