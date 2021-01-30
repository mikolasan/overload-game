#include "draw/console.h"
#include "elements/game_world.h"
#include "input.h"

int main(int argc, char const *argv[])
{
  auto renderer = std::make_unique<ConsoleRenderer>();
  auto game_world = std::make_unique<GameWorld>();
  auto input = std::make_unique<Input>();
  game_world->setup();
  game_world->update([&input, &game_world]() {
    game_world->update_input(input);
  });
  game_world->draw([&renderer, &game_world]() {
    renderer->draw(game_world);
  });
  game_world->loop();
  return 0;
}
