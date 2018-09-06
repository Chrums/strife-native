#include "Component.h"

#include "Entity.h"
    
//using boost::property_tree::ptree;
    
void Component::Register(void) {};

// ptree Component::Serialize(void) {
    
// }

// void Component::Deserialize(ptree data) {
    
// }

Component::Component(Entity* entity) :
    entity_(entity) {};
    
Component::Component(const boost::uuids::uuid identifier, Entity* entity) :
    Unique(identifier),
    entity_(entity) {};