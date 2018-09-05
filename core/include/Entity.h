#ifndef ENTITY_H
#define ENTITY_H

#include <optional>
#include <set>
#include <typeindex>
#include <typeinfo>
#include <vector>

#include <boost/uuid/uuid.hpp>

#include "Component.h"
#include "Unique.h"

class Scene;

class Entity : public Unique {
    
public:

    Entity(const Entity& entity);
    Entity(Scene* scene);
    Entity(const boost::uuids::uuid id, Scene* scene);
    
    Entity* GetParent(void);
    void SetParent(Entity* entity);
    std::vector<Entity*> GetChildren(void);
    void AddChild(Entity* entity);
    void RemoveChild(Entity* entity);
    
    Component* AddComponentByType(std::type_index type);
    void RemoveComponentByType(std::type_index type);
    Component* GetComponentByType(std::type_index type);
    
    template <typename T>
    T* AddComponent(void) {
        return static_cast<T*>(AddComponentByType(std::type_index(typeid(T))));
    }
    
    template <typename T>
    void RemoveComponent(void) {
        static_cast<T>(RemoveComponentByType(std::type_index(typeid(T))));
    }
    
    template <typename T>
    T* GetComponent(void) {
        return static_cast<T*>(GetComponentByType(std::type_index(typeid(T))));
    }
    
private:

    Scene* scene_;
    std::optional<boost::uuids::uuid> parentId_;
    std::set<boost::uuids::uuid> childrenIds_;
    
};

#endif