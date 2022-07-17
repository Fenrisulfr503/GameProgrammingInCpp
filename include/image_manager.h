#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_render.h"
#include <map>
#include <string>
class ImageManager {
public:
  ImageManager();
  ~ImageManager();
  bool LoadImage(std::string fileName);
  SDL_Texture *GetTexture(std::string &key) {
    auto search = mTexManager.find(key);
    if (search != mTexManager.end()) {
      return mTexManager[key];
    } else {
      return nullptr;
    }
  }

  void SetRendder(SDL_Renderer *rendder) { mRendder = rendder; }

private:
  std::map<std::string, SDL_Texture *> mTexManager;
  SDL_Renderer *mRendder;
};