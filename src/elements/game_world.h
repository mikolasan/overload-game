#pragma once

#include <functional>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <utility>
#include "../input.h"
#include "../logic/build.h"
#include "../logic/player.h"

class GameWorld
{
public:
  GameWorld();
  ~GameWorld();

  void setup();
  void update(std::function<void(void)> update_fn);
  void update_input(const std::unique_ptr<Input> &input);
  void draw(std::function<void(void)> draw_fn);
  void loop();

  void set_player_control(int player_id, int control);
  const std::shared_ptr<Player>& get_player(int id) const;
  void reset_player_order();
  void next_player();
  void on_next_player();
  void ai_turn(int player_id);
  void explode(std::shared_ptr<Player> player, int x, int y);
  template <class PositionCondition>
  int add_one_side(int x, int y, int k, int player_id, PositionCondition cond)
  {
    if (cond()) {
      start_building(x, y, k);
      return 0;
    } else {
      return k;
    }
  }
  int add_left(std::shared_ptr<Player> player, int x, int y, int k);
  int add_right(std::shared_ptr<Player> player, int x, int y, int k);
  int add_up(std::shared_ptr<Player> player, int x, int y, int k);
  int add_down(std::shared_ptr<Player> player, int x, int y, int k);
  int get_cursor_x() const;
  int get_cursor_y() const;
  std::pair<int, int> get_chips(int x, int y) const;
  void build_here(int x, int y, int k = 1);
  void start_building(int x, int y, int k = 1);
  void on_building_stopped();

  std::vector<std::vector<bool>> walls;
  std::vector<std::vector<int>> level_map;
  std::pair<int, int> cursor_position;

private:
  void read_level_map(std::string level_file);

  std::function<void(void)> _update_fn;
  std::function<void(void)> _draw_fn;
  bool _running;
  using Players = std::map<int, std::shared_ptr<Player>>;
  Players _players;
  Players::iterator _current_player;
  using Chips = std::map<std::pair<int, int>, std::shared_ptr<Chip>>;
  Chips _all_chips;
  std::list<std::unique_ptr<Build>> _sequence;
};