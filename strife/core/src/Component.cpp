#include "Component.h"

#include "Scene.h"
#include "Entity.h"

using boost::uuids::uuid;
using nlohmann::json;
    
void Component::initialize() {};

json Component::serialize() {
    json data;
    
    return data;
};

void Component::deserialize(json data) {
    
};

Component::Component(Entity* entity) :
    entity(entity) {};