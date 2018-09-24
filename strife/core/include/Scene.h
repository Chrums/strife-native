#ifndef SCENE_H
#define SCENE_H

#include <map>
#include <boost/uuid/uuid.hpp>
#include "Entity.h"

namespace Strife {
    
    class Scene {
        
    public:
    
        const Entity* const addEntity();
        const Entity* const addEntity(const boost::uuids::uuid id);
        void removeEntity(const Entity* const entity);
        
    private:
    
        std::set<Entity> entities_;
        
    };
    
}

#endif