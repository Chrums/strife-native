#ifndef ENTITY_H
#define ENTITY_H

#include <typeindex>
#include <set>

#include <boost/uuid/uuid.hpp>

#include <nlohmann/json.hpp>

#include "Component.h"
#include "Unique.h"

class Scene;

class Entity : public Unique {
    
public:

    Scene* const scene;

    Entity(const Entity& entity);
    Entity(Scene* scene);
    Entity(const boost::uuids::uuid id, Scene* scene);
    
    virtual nlohmann::json serialize();
    virtual void deserialize(nlohmann::json data);
    
    void setParent(Entity* entity);
    Entity* getParent();
    void addChild(Entity* entity);
    void removeChild(Entity* entity);
    std::set<Entity*> getChildren();
    
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
    
private:
    
    boost::uuids::uuid parentId_;
    std::set<boost::uuids::uuid> childrenIds_;
    
};

#endif