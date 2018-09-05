#ifndef COMPONENT_H
#define COMPONENT_H

#include "Unique.h"

class Entity;

class Component : public Unique {
    
public:
    
    void Initialize(void);
    void Update(void);
    void Render(void);
    
protected:

    Entity* entity_;
    
    Component(Entity* entity);
    Component(const boost::uuids::uuid identifier, Entity* entity);
    
};

#endif