#include "Component.h"

#include "Entity.h"

using namespace Strife;
using boost::uuids::uuid;

Component::Component(const Entity* const entity) :
    entity(entity) {};
    
Component::Component(const uuid id, const Entity* const entity) :
    Unique(id),
    entity(entity) {};