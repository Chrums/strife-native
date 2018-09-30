#ifndef COMPONENT_H
#define COMPONENT_H

#include "Unique.h"

namespace Strife {
    
    class Entity;
    
    class Component : public Unique {
        
    public:
        
        const Entity* const entity;
        
    protected:
        
        Component(const Entity* const entity);
        Component(const boost::uuids::uuid id, const Entity* const entity);
        
    };

}

#endif