#ifndef COMPONENT_H
#define COMPONENT_H

#include <boost/uuid/uuid.hpp>
#include <nlohmann/json.hpp>
#include "Entity.h"
#include "Unique.h"

namespace Strife {
    
    class Component : public Unique {
        
    public:
        
        const Entity entity;
        
        virtual const nlohmann::json serialize() const;
        virtual void deserialize(const nlohmann::json data);
        
    protected:
        
        Component(const Entity entity);
        Component(const boost::uuids::uuid id, const Entity entity);
        
    };

}

#endif