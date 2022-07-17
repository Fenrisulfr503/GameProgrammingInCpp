#include "game.h"
#include "SDL_image.h"
#include "SDL_render.h"
#include "SDL_rwops.h"
#include "SDL_surface.h"

Game::Game() {}
Game::~Game() {}
bool Game::Initialize() {
  int sdlResult = SDL_Init(SDL_INIT_VIDEO);
  if (sdlResult != 0) {
    SDL_Log("Unable to initialize SDL : %s", SDL_GetError());
    return false;
  }

  // Create SDL Window
  mWindow = SDL_CreateWindow("Game Programming in CPP", 100, 100, 1024, 768, 0);

  // Check window state
  if (!mWindow) {
    SDL_Log("Failed to create window: %s", SDL_GetError());
    return false;
  }

  mRenderer = SDL_CreateRenderer(
      mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  // Font
  TTF_Init();
  font = TTF_OpenFont("Comfortaa-Light.ttf", 30);

  SDL_Color White = {0, 200, 50};

  // as TTF_RenderText_Solid could only be used on
  // SDL_Surface then you have to create the surface first
  surfaceMessage = TTF_RenderText_Blended(font, "GAME OVER!", White);
  // now you can convert it into a texture
  Message = SDL_CreateTextureFromSurface(mRenderer, surfaceMessage);

  mTickCounts = SDL_GetTicks();

  // Initlization Balls
  BallDatas data1{{200, 200}, {3.0, 2.5}};
  mBalls.emplace_back(data1);
  BallDatas data2{{400, 300}, {2.0, 3.5}};
  mBalls.emplace_back(data2);
  BallDatas data3{{700, 600}, {-2.5, 4.5}};
  mBalls.emplace_back(data3);

  // Load Textures 
  mImageManager.SetRendder(mRenderer);
  mImageManager.LoadImage("sprites-cat-running.png");
  
  return true;
}

void Game::Shutdown() {
  SDL_DestroyRenderer(mRenderer);
  SDL_DestroyWindow(mWindow);

  TTF_CloseFont(font);
  TTF_Quit();
  SDL_FreeSurface(surfaceMessage);
  SDL_DestroyTexture(Message);
  SDL_Quit();
}

void Game::Runloop() {
  while (mIsRunning) {
    ProcessInput();
    UpdateGame();
    GenerateOutput();
  }
}

void Game::ProcessInput() {
  SDL_Event event;
  // While there are still events in the queue
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      mIsRunning = false;
      break;
    }
  }
  // Get state of keyboards
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  // If escape is pressd, also end loop
  if (state[SDL_SCANCODE_ESCAPE]) {
    mIsRunning = false;
  }

  if (state[SDL_SCANCODE_UP]) {
    controllerPosition -= controllerSpeed;
  }
  if (state[SDL_SCANCODE_DOWN]) {
    controllerPosition += controllerSpeed;
  }
}

void Game::UpdateGame() {

  if (mGameover) {
    return;
  }

  // Time Update
  while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTickCounts + 16)) {
  }
  float deltaTime = (SDL_GetTicks() - mTickCounts) / 1000.f;
  mTickCounts = SDL_GetTicks();

  // Clamp maximum delta time value
  if (deltaTime > 0.05f)
    deltaTime = 0.05f;
  mElapsedTime += deltaTime;
  if (mElapsedTime >= 1.f) {
    mFPS = static_cast<float>(mFrameCounts) / mElapsedTime;
    mFrameCounts = 0;
    mElapsedTime = 0;
  }

  // Update Actors
  mIsUpdateRunning = true;
  for (auto &it : mActors) {
    it->Update(deltaTime);
  }
  mIsUpdateRunning = false;

  // Move Pending Actor to Actor
  for (auto &it : mActors) {
    mActors.emplace_back(it);
  }
  mPendingActors.clear();

  // Limit controllerPosition
  controllerPosition =
      SDL_max(controllerPosition, thickness + controllerHeight * .5f);
  controllerPosition =
      SDL_min(controllerPosition, 768 - thickness - controllerHeight * .5f);

  // Check Collisions

  for (BallDatas &ballData : mBalls) {
    if (ballData.position.x <= controllerThickness + ballSize * 0.5f) {
      if (ballData.position.y > controllerPosition - controllerHeight * 0.5f &&
          ballData.position.y < controllerPosition + controllerHeight * 0.5f) {
        ballData.direction.x *= -1;
      } else {
        mGameover = true;
      }
    }
    if (ballData.position.x >= 1024 - thickness - ballSize * 0.5f) {
      ballData.direction.x *= -1;
    }

    if (ballData.position.y <= thickness + ballSize * 0.5f) {
      ballData.direction.y *= -1;
    }
    if (ballData.position.y >= 768 - thickness - ballSize * 0.5f) {
      ballData.direction.y *= -1;
    }

    // Update ball Position
    ballData.position.x += ballData.direction.x * ballSpeed * deltaTime;
    ballData.position.y += ballData.direction.y * ballSpeed * deltaTime;
  }

  // SDL Button API Use Example
  // if ((state & SDL_BUTTON_LMASK) != 0) {
  //   ballPosition.x = static_cast<float>(x);
  //   ballPosition.y = static_cast<float>(y);
  //   ballSize += 0.2f;
  //   SDL_Log("Mouse Button 1 (left) is pressed.");
  // }
}
void Game::GenerateOutput() {

  // Render Font for GameOver
  if (mGameover) {
    SDL_Rect Message_rect{512 - surfaceMessage->w / 2,
                          389 - surfaceMessage->h / 2, surfaceMessage->w,
                          surfaceMessage->h};
    SDL_RenderCopy(mRenderer, Message, NULL, &Message_rect);
    SDL_RenderPresent(mRenderer);
    return;
  }

  // Draw Background and Wall
  SDL_Rect topWall{0, 0, 1024, thickness};
  SDL_Rect bottomWall{1024 - thickness, 0, thickness, 1024};
  SDL_Rect leftWall{0, 768 - thickness, 1024, thickness};

  SDL_Color wallColor{85, 0, 0, 255};
  SDL_Color backgroundColor{25, 25, 25, 255};
  SDL_SetRenderDrawColor(mRenderer, backgroundColor.r, backgroundColor.g,
                         backgroundColor.b, backgroundColor.a);
  SDL_RenderClear(mRenderer);
  SDL_SetRenderDrawColor(mRenderer, wallColor.r, wallColor.g, wallColor.b,
                         wallColor.a);
  SDL_RenderFillRect(mRenderer, &topWall);
  SDL_RenderFillRect(mRenderer, &bottomWall);
  SDL_RenderFillRect(mRenderer, &leftWall);

  // Draw Controller
  SDL_Color controllerColor{100, 150, 150, 255};
  SDL_SetRenderDrawColor(mRenderer, controllerColor.r, controllerColor.g,
                         controllerColor.b, controllerColor.a);
  SDL_Rect controller{
      0, static_cast<int>(controllerPosition - controllerHeight * 0.5f),
      static_cast<int>(controllerThickness),
      static_cast<int>(controllerHeight)};

  SDL_RenderFillRect(mRenderer, &controller);
  // Draw Ball

  for (BallDatas &ballData : mBalls) {
    SDL_Color ballColor{100, 100, 100, 255};
    SDL_SetRenderDrawColor(mRenderer, ballColor.r, ballColor.g, ballColor.b,
                           ballColor.a);
    SDL_Rect ball{static_cast<int>(ballData.position.x - ballSize * 0.5),
                  static_cast<int>(ballData.position.y - ballSize * 0.5),
                  static_cast<int>(ballSize), static_cast<int>(ballSize)};
    SDL_RenderFillRect(mRenderer, &ball);
  }

  // Draw FPS
  SDL_Color Color = {0, 200, 50};

  // as TTF_RenderText_Solid could only be used on
  // SDL_Surface then you have to create the surface first
  char buf[6] = "";
  SDL_itoa(static_cast<int>(mFPS * 100), buf, 10);
  buf[3] = buf[2];
  buf[4] = buf[3];
  buf[2] = '.';

  SDL_Surface *surfaceFPS = TTF_RenderText_Blended(font, buf, Color);
  // now you can convert it into a texture
  SDL_Texture *FPS = SDL_CreateTextureFromSurface(mRenderer, surfaceFPS);

  SDL_Rect FPS_rect{0, 10, surfaceFPS->w, surfaceFPS->h};
  SDL_RenderCopy(mRenderer, FPS, NULL, &FPS_rect);

  SDL_RenderPresent(mRenderer);
  mFrameCounts += 1;
}

void Game::AddActor(Actor *actor) {
  if (mIsUpdateRunning) {
    mPendingActors.emplace_back(actor);
  } else {
    mActors.emplace_back(actor);
  }
}