#ifndef SCENE_H
#define SCENE_H

#include <map>
#include <boost/uuid/uuid.hpp>
#include "Entity.h"

namespace Strife {
    
    class Scene {
        
    public:
    
        Entity* const addEntity();
        Entity* const addEntity(const boost::uuids::uuid id);
        void removeEntity(const Entity* const entity);
        Entity* const getEntity(const boost::uuids::uuid id) const;
        void moveEntity(Entity* const entity, Entity* const target);
        
    private:
    
        std::map<boost::uuids::uuid, Entity> entities_;
        
    };
    
}

#endif