#include "image_manager.h"
#include "SDL_image.h"
#include "SDL_render.h"
#include "SDL_surface.h"

ImageManager::ImageManager() { IMG_Init(IMG_INIT_PNG); }
ImageManager::~ImageManager() {
  for (const auto &iter : mTexManager) {
    SDL_DestroyTexture(iter.second);
  }
}
bool ImageManager::LoadImage(std::string fileName) {
  SDL_Surface *surf = IMG_Load(fileName.data());
  if (!surf) {
    SDL_Log("Fail to load texture file %s", fileName.data());
    return false;
  }

  SDL_Texture *tex = SDL_CreateTextureFromSurface(mRendder, surf);
  SDL_FreeSurface(surf);
  if (!tex) {
    SDL_Log("Fail to convert surface to texture for  %s", fileName.data());
    return false;
  }

  mTexManager[fileName] = tex;

  return true;
}