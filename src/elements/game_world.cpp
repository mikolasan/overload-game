#include "game_world.h"
#include "../draw/renderer.h"
#include <fstream>
#include <iostream>
#include <curses.h>
#include <random>

GameWorld::GameWorld() : _running(false)
{
}

GameWorld::~GameWorld() {}

void GameWorld::setup()
{
  read_level_map("field1.txt");
  if (_players.empty()) {
    std::cerr << "No players!\n";
  }
  set_player_control(42, 666);
  reset_player_order();
}

void GameWorld::set_player_control(int player_id, int control) {
  _players[1]->control_type = Player::ControlType::HUMAN;
  _players[2]->control_type = Player::ControlType::AI;
  _players[3]->control_type = Player::ControlType::AI;
  _players[4]->control_type = Player::ControlType::AI;
}

void GameWorld::reset_player_order() {
  _current_player = _players.begin();
}

void GameWorld::next_player() {
  ++_current_player;
  if (_current_player == _players.end()) {
    _current_player = _players.begin();
  }
  on_next_player();
}

void GameWorld::on_next_player() {
  if (_current_player->second->control_type == Player::ControlType::AI) {
    ai_turn(_current_player->first);
  }
  // else wait for the player
}

void GameWorld::ai_turn(int player_id) {
  auto& chips = _players[player_id]->chips;
  std::random_device rd{};
  std::mt19937 gen{rd()};
  std::uniform_int_distribution<> d(0, chips.size() - 1);
  int r = d(gen);
  auto it = chips.begin();
  std::advance(it, r);
  auto player = _players[player_id];
  auto [x, y] = it->first;
  _players[player_id]->build_here(x, y, 1, [this, player](int x, int y) {
    explode(player, x, y);
  });
  return next_player();
}

void GameWorld::explode(std::shared_ptr<Player> player, int x, int y)
{
  player->chips[{x, y}].size -= 4;
  int remaining = 0;
  remaining = add_left(player, x, y, 1);
  remaining = add_right(player, x, y, 1 + remaining);
  if (remaining == 1) {
    remaining = add_left(player, x, y, 1);
  }

  remaining = add_up(player, x, y, 1);
  remaining = add_down(player, x, y, 1 + remaining);
  if (remaining == 1) {
    remaining = add_up(player, x, y, 1);
  }
}

int GameWorld::add_left(std::shared_ptr<Player> player, int x, int y, int k)
{
  if (0 < x - 1 && x - 1 < level_map[y].size() && level_map[y][x - 1] != -1) {
    player->build_here(x - 1, y, k, [this, player](int x, int y) {
      explode(player, x - 1, y);
    });
    level_map[y][x - 1] = player->id;
    return 0;
  } else {
    return k;
  }  
}

int GameWorld::add_right(std::shared_ptr<Player> player, int x, int y, int k)
{
  if (0 < x + 1 && x + 1 < level_map[y].size() && level_map[y][x + 1] != -1) {
    player->build_here(x + 1, y, k, [this, player](int x, int y) {
      explode(player, x + 1, y);
    });
    level_map[y][x + 1] = player->id;
    return 0;
  } else {
    return k;
  }
}

int GameWorld::add_down(std::shared_ptr<Player> player, int x, int y, int k)
{
  if (0 < y + 1 && y + 1 < level_map.size() && level_map[y + 1][x] != -1) {
    player->build_here(x, y + 1, k, [this, player](int x, int y) {
      explode(player, x, y + 1);
    });
    level_map[y + 1][x] = player->id;
    return 0;
  } else {
    return k;
  }
}

int GameWorld::add_up(std::shared_ptr<Player> player, int x, int y, int k)
{
  if (0 < y - 1 && y - 1 < level_map.size() && level_map[y - 1][x] != -1) {
    player->build_here(x, y - 1, k, [this, player](int x, int y) {
      explode(player, x, y - 1);
    });
    level_map[y - 1][x] = player->id;
    return 0;
  } else {
    return k;
  }
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
    case 13: {// enter
    
      auto player = _current_player->second;
      auto result = _current_player->second->build_here(get_cursor_x(), get_cursor_y(), 1, [this, player](int x, int y) {
        explode(player, x, y);
      });
      if (result) {
        next_player();
      }
      break;
    }
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

int GameWorld::get_cursor_x() const
{
  return std::get<0>(cursor_position);
}

int GameWorld::get_cursor_y() const
{
  return std::get<1>(cursor_position);
}

const std::shared_ptr<Player> &GameWorld::get_player(int id) const
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