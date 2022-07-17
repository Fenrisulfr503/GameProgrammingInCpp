#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include "image_manager.h"
#include "actor.h"
#include <vector>

#include "data.h"

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

  int thickness{10};

  // Ball Variables
  float ballSize{20.f};
  // Vector2 ballPosition{200.f, 200.f};
  // Vector2 ballDirection{1.0f, 0.5f};
  float ballSpeed = 100.f;
  std::vector<BallDatas> mBalls;

  float controllerPosition = 768.f * .5f;
  float controllerThickness = 10.f;
  float controllerHeight = 80.f;
  float controllerSpeed = 5.f;

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
};