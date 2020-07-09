#include "draw/console.h"
#include "elements/game_world.h"

int main(int argc, char const *argv[])
{
  auto renderer = std::make_unique<ConsoleRenderer>();
  auto game_world = std::make_unique<GameWorld>();
  game_world->setup();
  renderer->draw(game_world);
  return 0;
}
