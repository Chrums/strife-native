#include "Component.h"

#include "Entity.h"
    
using boost::uuids::uuid;
    
void Component::initialize() {};

Component::Component(Entity* entity) :
    entity_(entity) {};
    
Component::Component(const uuid id, Entity* entity) :
    Unique(id),
    entity_(entity) {};