#ifndef ENTITY_H
#define ENTITY_H

#include <set>
#include <typeindex>
#include <boost/uuid/uuid.hpp>
#include <nlohmann/json.hpp>
#include "Hierarchy.h"
#include "Unique.h"

namespace Strife {
    
    class Scene;
    
    class Entity : public Unique {
        
    public:
        
        Scene* scene;
        
        Entity(const Entity& entity);
        Entity(Scene* scene);
        Entity(const boost::uuids::uuid id, Scene* scene);
    
    };
    
}

#endif