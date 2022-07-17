#include "component.h"

Component::Component(Actor *Owner, int updateOrder)
    : mOwner(Owner), mUpdateOrder(updateOrder) {}

Component::~Component()
{

}

void Component::Update(float deltaTime)
{
    
}