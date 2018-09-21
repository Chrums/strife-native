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
    
    class Entity : public Unique, public Hierarchy<boost::uuids::uuid> {
        
    public:
        
        Scene* scene;
        
        Entity(const Entity& entity);
        Entity(Scene* scene);
        Entity(const boost::uuids::uuid id, Scene* scene);
        
        void setParent(const Entity* const parent);
        Entity* const getParent() const;
        void addChild(const Entity* const child);
        void removeChild(const Entity* const child);
        const std::set<Entity*> getChildren() const;
        void move(Entity* const target);
            
    };
    
}

#endif