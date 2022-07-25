#include "BGSprite_component.h"
#include "actor.h"
#include "sprite_component.h"

BGSpriteComponent::BGSpriteComponent(Actor *owner, int drawOrder)
    : SpriteComponent(owner, drawOrder) {}

BGSpriteComponent::~BGSpriteComponent() {}

void BGSpriteComponent::Draw(SDL_Renderer *renderer)
{
    
}