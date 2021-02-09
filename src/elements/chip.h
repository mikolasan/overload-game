#pragma once

struct Chip
{
  int x;
  int y;
  int player_id;
  int size;
  Chip() {}
  Chip(int a_x, int a_y, int a_player_id, int a_size) :
    x(a_x), y(a_y), player_id(a_player_id), size(a_size)
    {}
};