#pragma once

#include "SDL_render.h"
#include "component.h"
class SpriteComponent : public Component {
public:
  SpriteComponent(class Actor *owner, int drawOrder = 100);
  ~SpriteComponent();

  virtual void Draw(SDL_Renderer *renderer);
  virtual void SetTexture(SDL_Texture *texture);

  int GetDrawOrder() const { return mDrawOrder; }
  int GetTexHeight() const { return mTexHeight; }
  int GetTexWidth() const { return mTexWidth; }

protected:
    SDL_Texture* mTex;
    int mDrawOrder;
    int mTexHeight;
    int mTexWidth;
};