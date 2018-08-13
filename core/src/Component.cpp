#include "Component.h"

#include "Entity.h"

Component::Component(Entity* entity) :
    entity_(entity) {}
    
Component::Component(const boost::uuids::uuid identifier, Entity* entity) :
    Unique(identifier),
    entity_(entity) {}