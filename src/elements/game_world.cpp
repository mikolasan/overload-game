#include "../draw/renderer.h"
#include "game_world.h"
#include <fstream>
#include <iostream>
#include <curses.h>

GameWorld::GameWorld() : _running(false)
{
}

GameWorld::~GameWorld() {}

void GameWorld::setup()
{
  read_level_map("field1.txt");
}

void GameWorld::update_input(const std::unique_ptr<Input> &input)
{
  auto key = input->get_key();
  if (key != ERR)
  {
    switch (key)
    {
    case 'q':
      _running = false;
      break;
    case 'w':
      std::get<0>(cursor_position)--;
      break;
    case 's':
      std::get<0>(cursor_position)++;
      break;
    case 'a':
      std::get<1>(cursor_position)--;
      break;
    case 'd':
      std::get<1>(cursor_position)++;
      break;
    }
  }
}
void GameWorld::update(std::function<void(void)> update_fn)
{
  _update_fn = update_fn;
}

void GameWorld::draw(std::function<void(void)> draw_fn)
{
  _draw_fn = draw_fn;
}

void GameWorld::loop()
{
  _running = true;
  while (_running)
  {
    _update_fn();
    _draw_fn();
  }
}

void GameWorld::read_level_map(std::string level_file)
{
  std::ifstream file(level_file);
  if (!file.is_open())
  {
    std::cerr << "error loading battleground";
    return;
  }

  std::string line;
  while (std::getline(file, line))
  {
    size_t line_size = line.size();
    std::vector<bool> row(line_size, false);
    std::vector<bool>::iterator flags = row.begin();

    // int nmax = 0;
    for (auto it = line.begin(); it != line.end(); ++it)
    {
      char sym = *it;
      switch (sym)
      {
      case '0':
        //isWall
        *flags = true;
        break;
      case '1':
        //empty cell
        break;
      case '2':
        //player start position
        // plyr++;
        // listob one;				//local exhibit vector of players
        // one.chp_count = STARTF;
        // one.plr = plyr;
        // gamers.push_back(one);
        // for (int g = 0; g < STARTF; g++)
        //   addChip(m, nmax, plyr);
        break;
      }
      // nmax++;
      flags++;
    }

    // if(nmax > n) n = nmax;
    // if(nmax > 0) m++;
    level_map.push_back(row);
  }
  file.close();
}