#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <map>
#include <numeric>
#include <typeindex>
#include <typeinfo>
#include <vector>

#include "Component.h"
#include "Entity.h"
#include "System.h"

class Scene {
    
public:
    
    void Initialize(void);
    void Update(void);
    void Render(void);
    
    Entity* AddEntity(void);
    Entity* AddEntity(Entity* parent);
    Entity* AddEntity(boost::uuids::uuid id, Entity* parent);
    void RemoveEntity(Entity* entity);
    void MoveEntity(Entity* entity, Entity* target);
    Entity* GetEntityById(const boost::uuids::uuid id);
    
    Component* AddComponentByTypeAndEntity(std::type_index type, Entity* entity);
    void RemoveComponentByTypeAndEntity(std::type_index type, Entity* entity);
    Component* GetComponentByTypeAndEntity(std::type_index type, Entity* entity);
    
    template <typename T>
    void Register() {
        systems_[std::type_index(typeid(T))] = new System<T>();
    };
    
    template <typename S, typename T, typename... Args>
    void Register(Args... args) {
        systems_[std::type_index(typeid(T))] = new S(args...);
    }
    
    template <typename T>
    T* AddComponentByEntity(Entity* entity) {
        return static_cast<System<T>*>(systems_[std::type_index(typeid(T))])->Add(entity);
    };
    
    template <typename T>
    void RemoveComponentByEntity(Entity* entity) {
        static_cast<System<T>*>(systems_[std::type_index(typeid(T))])->Remove(entity);
    };
    
    template <typename T>
    T* GetComponentByEntity(Entity* entity) {
        return static_cast<System<T>*>(systems_[std::type_index(typeid(T))])->At(entity);
    };
    
private:

    std::map<boost::uuids::uuid, Entity> entities_;
    std::map<std::type_index, ISystem*> systems_;
    
};

#endif