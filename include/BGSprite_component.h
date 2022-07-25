#pragma once

#include "sprite_component.h"
class BGSpriteComponent : public SpriteComponent {
public:
  BGSpriteComponent(class Actor *owner, int drawOrder = 100);
  ~BGSpriteComponent();
  void Draw(SDL_Renderer *renderer) override;
};