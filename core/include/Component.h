#ifndef COMPONENT_H
#define COMPONENT_H

#include "Unique.h"

class Entity;

class Component : public Unique {
public:
    Component(Entity& entity);
    Component(const boost::uuids::uuid identifier, Entity& entity);
    Component& operator=(const Component& component);
protected:
    Entity& entity_;
};

#endif