#include "sprite_component.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "actor.h"
#include "component.h"
#include "game.h"
SpriteComponent::SpriteComponent(Actor *owner, int drawOrder)
    : Component(owner) {
        owner->GetGame()->AddSprite(this);
    }

SpriteComponent::~SpriteComponent()
{

}

void SpriteComponent::Draw(SDL_Renderer *renderer)
{
    if(mTex)
    {
        SDL_Rect r;
        r.w = static_cast<int>( mTexWidth * mOwner->GetScale());
        r.h = static_cast<int>( mTexHeight * mOwner->GetScale());
        r.x = static_cast<int>( mOwner->GetTransform().x - r.w * 0.5f);
        r.y = static_cast<int>( mOwner->GetTransform().y - r.h * 0.5f);

        SDL_RenderCopyEx(renderer,mTex, nullptr, &r, 0.0, nullptr, SDL_FLIP_NONE);
    }
}

void SpriteComponent::SetTexture(SDL_Texture *texture)
{
    mTex = texture;
    SDL_QueryTexture(mTex, nullptr, nullptr, &mTexWidth, &mTexHeight);

}
