#pragma once


#include <vector>
#include "data.h"
class Component;
class Game;

class Actor {
public:
  enum class EState { EActive = 0, EPaused, EDead };

  Actor(Game *game);
  virtual ~Actor();
  void Update(float deltaTime);
  void UpdateComponents(float deltaTime);
  virtual void UpdateActor(float deltaTime);

  // Setter/ Getter
  void SetState(EState state);
  void SetTransform(Vector2 trans);
  void SetScale(float scale);
  EState GetState();
  Vector2 GetTransform();
  float GetScale();
  Game* GetGame() const { return mGame;}
  // Add/ Remove Components
  void AddComponent(Component *component);
  void RemoveComponent(Component *component);

private:
  EState mState;
  Vector2 mTransform;
  float mScale;

  std::vector<Component *> mComponents;
  Game *mGame;

};