#include <memory>

#include "build.h"
#include "../elements/game_world.h"

class ChipBuild : public Build {
public:
  ChipBuild(std::shared_ptr<GameWorld> game_world, int x, int y, int player_id, int k = 1) :
    _game_world(game_world), _x(x), _y(y), _player_id(player_id), _k(k)
  {}
  void exec() override {
    _game_world->build_here(_x, _y, _k);
  }
private:
  std::shared_ptr<GameWorld> _game_world;
  int _x;
  int _y;
  int _player_id;
  int _k;
};