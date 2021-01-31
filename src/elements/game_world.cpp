#include "game_world.h"
#include "../draw/renderer.h"
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

const std::unique_ptr<Player> &GameWorld::get_player(int id) const
{
  return _players.at(id);
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
  int y = 0;
  while (std::getline(file, line))
  {
    size_t line_size = line.size();
    std::vector<int> row(line_size);
    auto marker = row.begin();
    std::vector<bool> wall_line(line_size, false);
    auto wall_marker = wall_line.begin();

    int x = 0;
    for (auto it = line.begin(); it != line.end(); ++it)
    {
      char sym = *it;
      switch (sym)
      {
      case '#':
        *wall_marker = true;
        *marker = -1;
        break;
      case '.':
        // empty cell
        break;
      case '1':
      case '2':
      case '3':
      case '4':
      {
        // players
        int id = sym - '0';
        *marker = id;
        _players[id] = std::make_unique<Player>(x, y, id);
        break;
      }
      default:
        std::cerr << "read unknown symbol '" << sym << "'\n";
        break;
      }
      ++wall_marker;
      ++marker;
      ++x;
    }
    ++y;

    walls.push_back(wall_line);
    level_map.push_back(row);
  }
  file.close();
}