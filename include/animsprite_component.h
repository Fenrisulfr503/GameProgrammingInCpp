#pragma once

#include "sprite_component.h"

class AnimSpriteComponent : public SpriteComponent {
public:
  AnimSpriteComponent(class Actor *owner, int drawOrder = 100);
  ~AnimSpriteComponent();
  void Update(float deltaTime) override;
  void Draw(SDL_Renderer *renderer) override;
  float GetFps() const { return mFps; }

  void SetFps(float fps) { mFps = fps; }
  void SetSliceNumber(int width_num, int height_num);

private:
  float mFrame{0.f};
  float mFps{0.f};

  int mWidthNumber{0};
  int mHeightNumber{0};
};