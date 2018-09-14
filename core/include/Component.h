#ifndef COMPONENT_H
#define COMPONENT_H

#include <nlohmann/json.hpp>

#include "Unique.h"

class Scene;
class Entity;

class Component : public Unique {
    
public:
    
    Entity* entity;
    
    virtual void initialize();
    
    virtual nlohmann::json serialize();
    virtual void deserialize(nlohmann::json data);
    
protected:
    
    Component(Entity* entity);
    Component(const boost::uuids::uuid id, Entity* entity);
    
};

#endif