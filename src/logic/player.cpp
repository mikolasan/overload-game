#include "player.h"

bool Player::build_here(int x, int y, int k, std::function<void(int, int)> callback)
{
  chips[{x, y}].size +=k;
  chips[{x, y}].player_id = id;
  _total_n_chips += k;
  if (chips[{x, y}].size >= 4) {
    callback(x, y);
  }
  return true;
}

// void Player::explode(int x, int y)
// {
  
// }