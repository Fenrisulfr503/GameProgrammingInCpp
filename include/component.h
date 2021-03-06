#pragma once

class Actor;

class Component {

public:
    Component(Actor* Owner, int updateOrder = 100);
    virtual ~Component();

    virtual void Update(float deltaTime);
    int GetUpdateOrder() const {return mUpdateOrder;}

private:
    Actor* mOwner;
    int mUpdateOrder;
};