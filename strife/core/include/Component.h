#ifndef COMPONENT_H
#define COMPONENT_H

#include <nlohmann/json.hpp>

class Scene;
class Entity;

class Component {
    
public:
    
    Entity* entity;
    
    virtual void initialize();
    
    virtual nlohmann::json serialize();
    virtual void deserialize(nlohmann::json data);
    
protected:
    
    Component(Entity* entity);
    
};

#endif