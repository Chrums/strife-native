#ifndef ENTITY_H
#define ENTITY_H

#include <typeindex>

#include <boost/uuid/uuid.hpp>

#include <nlohmann/json.hpp>

#include "Component.h"
#include "Unique.h"

using namespace std;

class Scene;

class Entity : public Unique {
    
public:

    Scene* scene;

    Entity(const Entity& entity);
    Entity(Scene* scene);
    Entity(const boost::uuids::uuid id, Scene* scene);
    
    virtual nlohmann::json serialize();
    virtual void deserialize(nlohmann::json data);
    
    Component* addComponent(std::type_index type);
    void removeComponent(std::type_index type);
    Component* getComponent(std::type_index type);
    
    template <typename T>
    T* addComponent(void) {
        return static_cast<T*>(addComponent(std::type_index(typeid(T))));
    }
    
    template <typename T>
    void removeComponent(void) {
        static_cast<T>(removeComponent(std::type_index(typeid(T))));
    }
    
    template <typename T>
    T* getComponent(void) {
        return static_cast<T*>(getComponent(std::type_index(typeid(T))));
    }
    
};

#endif