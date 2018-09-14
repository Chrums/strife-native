#include "Component.h"

#include "Scene.h"
#include "Entity.h"

using boost::uuids::uuid;
using nlohmann::json;
    
void Component::initialize() {};

json Component::serialize() {
    return json();
};

void Component::deserialize(json data) {};

Component::Component(Entity* entity) :
    entity(entity) {};
    
Component::Component(const uuid id, Entity* entity) :
    Unique(id),
    entity(entity) {};