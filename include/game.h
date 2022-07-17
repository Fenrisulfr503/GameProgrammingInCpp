#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include "image_manager.h"
#include "actor.h"
#include <vector>

#include "data.h"
#include "sprite_component.h"

class Actor;
class BallDatas
{
public:
  Vector2 position;
  Vector2 direction;
};


class Game {
public:
  Game();
  ~Game();
  // Initialize for game
  bool Initialize();
  // Runs the game loop until the game is over
  void Runloop();
  // Shutdown the game
  void Shutdown();

  void AddActor(Actor* actor);
  void AddSprite(SpriteComponent* sprite);
private:
  // Helper functions for the game loop
  void ProcessInput();
  void UpdateGame();
  void GenerateOutput();



  SDL_Window *mWindow;
  SDL_Renderer *mRenderer;
  bool mIsRunning;
  bool mGameover{false};

  Uint32 mTickCounts;
  float mElapsedTime{0};
  float mFPS{0.f};
  int mFrameCounts{0};

  // Fonts
  TTF_Font *font;
  SDL_Surface *surfaceMessage;
  SDL_Texture *Message;

  // Actors
  std::vector<Actor*> mActors;
  std::vector<Actor*> mPendingActors;
  bool mIsUpdateRunning { false };

  // Texture Manager
  ImageManager mImageManager;

  //SpriteComponents Manager
  std::vector<SpriteComponent*> mSpriteManager;

};