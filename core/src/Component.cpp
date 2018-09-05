#include "Component.h"

#include "Entity.h"
    
void Component::Initialize(void) {};

void Component::Update(void) {};

void Component::Render(void) {};

Component::Component(Entity* entity) :
    entity_(entity) {};
    
Component::Component(const boost::uuids::uuid identifier, Entity* entity) :
    Unique(identifier),
    entity_(entity) {};