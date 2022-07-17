#include "actor.h"
#include "component.h"
#include "game.h"

Actor::Actor(Game *game) : mGame(game) {}

Actor::~Actor() {}

void Actor::Update(float deltaTime) {
  this->UpdateComponents(deltaTime);
  this->UpdateActor(deltaTime);
}

void Actor::UpdateComponents(float deltaTime) {
  for (Component *comp : mComponents) {
    comp->Update(deltaTime);
  }
}

void Actor::UpdateActor(float deltaTime) {}

void Actor::AddComponent(Component *component) {
  for (auto it = mComponents.begin(); it != mComponents.end(); ++it) {
    if (component->GetUpdateOrder() < (*it)->GetUpdateOrder()) {
      mComponents.insert(it, component);
      break;
    }
  }
}

void Actor::RemoveComponent(Component *component) {
  for (auto it = mComponents.begin(); it != mComponents.end(); ++it) {
    if (component == (*it)) {
      mComponents.erase(it);
      break;
    }
  }
}

void Actor::SetState(Actor::EState state) { mState = state; }
void Actor::SetTransform(Vector2 trans) { mTransform = trans; }
void Actor::SetScale(float scale) { mScale = scale; }
Actor::EState Actor::GetState() { return mState; }
Vector2 Actor::GetTransform() { return mTransform; }
float Actor::GetScale() { return mScale; }