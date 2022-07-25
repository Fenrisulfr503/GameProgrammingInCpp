#define SDL_MAIN_HANDLED

#include "SDL.h"
#include "game.h"
#include <iostream>

int main(int argc, char **argv) {
  Game game;
  bool success = game.Initialize();

  
  if (success) {
    game.Runloop();
  }
  game.Shutdown();

  std::cout << "Hello,World!" << std::endl;
  return 0;
}