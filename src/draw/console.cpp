#include "console.h"
#include <iostream>
#include <curses.h>

ConsoleRenderer::ConsoleRenderer()
    : _running(false)
{
  initscr();
  noecho();
  cbreak();
  nonl();
  // keypad(stdscr, TRUE);
  curs_set(0);
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
  for (int i = 0; i < map.size(); ++i)
  {
    //for (auto line : map) {
    //for (auto b : line) {
    for (int j = 0; j < map[i].size(); ++j)
    {
      move(i, j); // y, x
      addch(map[i][j] ? '0' : '.');
      //std::cout << b ? "0" : ".";
    }
    //std::cout << std::endl;
  }
  printw("Cursor: %d %d\n", std::get<0>(world->cursor_position), std::get<1>(world->cursor_position));
  napms(12);
  // move(LINES - 1, COLS - 1);
  refresh();
}

void ConsoleRenderer::stop()
{
  _running = false;
}