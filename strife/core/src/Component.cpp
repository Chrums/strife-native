#include "Component.h"

using namespace Strife;
using boost::uuids::uuid;
using nlohmann::json;

Component::Component(const Entity entity) :
    entity(entity) {};
    
Component::Component(const uuid id, const Entity entity) :
    Unique(id),
    entity(entity) {};
    
const json Component::serialize() const {
    return json();
};

void Component::deserialize(const json data) {};