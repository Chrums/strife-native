#ifndef COMPONENT_H
#define COMPONENT_H

#include "Unique.h"

class Entity;

class Component : public Unique {
    
public:
    
    virtual void initialize();
    
    //virtual boost::property_tree::ptree Serialize();
    //virtual void Deserialize(boost::property_tree::ptree data);
    
protected:

    Entity* entity_;
    
    Component(Entity* entity);
    Component(const boost::uuids::uuid id, Entity* entity);
    
};

#endif