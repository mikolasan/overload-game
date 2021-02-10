#include "console.h"
#include <iostream>
#include <curses.h>

namespace
{
  void set_color(int color_id, short foreground_color)
  {
    init_pair(color_id, foreground_color, COLOR_BLACK);
  }
};

ConsoleRenderer::ConsoleRenderer()
    : _running(false)
{
  initscr();
  noecho();
  cbreak();
  nonl();
  // keypad(stdscr, TRUE);
  curs_set(0);

  if (has_colors())
  {
    start_color();
  }
  set_color(1, COLOR_RED);
  set_color(2, COLOR_GREEN);
  set_color(3, COLOR_WHITE);
  set_color(4, COLOR_YELLOW);
}

ConsoleRenderer::~ConsoleRenderer()
{
  standend();
  refresh();
  curs_set(1);
  endwin();
}

void ConsoleRenderer::draw(const std::unique_ptr<GameWorld> &world)
{  
  auto map = world->level_map;
  auto [cursor_x, cursor_y] = world->cursor_position;
  attrset(A_NORMAL);
  erase();
  for (int y = 0; y < map.size(); ++y)
  {
    //for (auto line : map) {
    //for (auto b : line) {
    for (int x = 0; x < map[y].size(); ++x)
    {
      chtype bold = (cursor_x == x && cursor_y == y) ? A_BOLD : A_NORMAL;
      move(y, x);
      auto cell = map[y][x];
      if (cell == 0)
      {
        attrset(bold);
        addch('.');
      }
      else if (cell >= 0)
      {
        // int player_id = cell;
        // const auto& player = world->get_player(player_id);
        auto [player_id, n_chips] = world->get_chips(x, y);
        attrset(COLOR_PAIR(player_id) | bold);
        addch('0' + n_chips);
      }
      else
      {
        attrset(bold);
        addch('#');
      }
      
      //std::cout << b ? "0" : ".";
    }
    //std::cout << std::endl;
  }
  // printw("Cursor: %d %d\n", cursor_x, cursor_y);
  napms(5);
  // move(LINES - 1, COLS - 1);
  refresh();
}

void ConsoleRenderer::stop()
{
  _running = false;
}