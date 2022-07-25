#include "animsprite_component.h"
#include "SDL_rect.h"
#include "actor.h"
#include "sprite_component.h"

#include <SDL.h>

AnimSpriteComponent::AnimSpriteComponent(Actor *owner, int drawOrder)
    : SpriteComponent(owner, drawOrder) {}

AnimSpriteComponent::~AnimSpriteComponent() {}

void AnimSpriteComponent::SetSliceNumber(int width_num, int height_num) {
  mWidthNumber = width_num;
  mHeightNumber = height_num;
}

void AnimSpriteComponent::Draw(SDL_Renderer *renderer) {
  // SDL_Log( "[AnimSpriteComponent Draw]" );
  int xNum = static_cast<int>(mFrame) % mWidthNumber;
  int yNum = static_cast<int>(mFrame / mWidthNumber) % mHeightNumber;

  int ratio = mWidthNumber / mHeightNumber;
  int sigleWidth = mTexWidth / mWidthNumber;
  int sigleHeight = mTexHeight / mHeightNumber;

  if (mTex) {
    SDL_Rect r;
    r.w = static_cast<int>(mTexWidth * mOwner->GetScale() / ratio);
    r.h = static_cast<int>(mTexHeight * mOwner->GetScale());
    r.x = static_cast<int>(mOwner->GetTransform().x - r.w * .5f);
    r.y = static_cast<int>(mOwner->GetTransform().y - r.h * .5f);
    SDL_Rect s;
    s.w = sigleWidth;
    s.h = sigleHeight;
    s.x = sigleWidth * xNum;
    s.y = sigleHeight * yNum;

    SDL_RenderCopyEx(renderer, mTex, &s, &r, 0.0, nullptr, SDL_FLIP_NONE);
  }
}

void AnimSpriteComponent::Update(float deltaTime) {
  SpriteComponent::Update(deltaTime);
  // SDL_Log( "[AnimSpriteComponent Update]" );
  mFrame += mFps * deltaTime;
}
