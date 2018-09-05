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
#include "Storage.h"

class Scene {
    
public:
    
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
    void RegisterComponent() {
        components_[std::type_index(typeid(T))] = new Storage<T>();
    }
    
    // template <typename S, typename T, typename... Args>
    // void RegisterComponent(Args... args) {
    //     components_[std::type_index(typeid(T))] = new S<T>(args...);
    // }
    
    template <typename T>
    T* AddComponentByEntity(Entity* entity) {
        return static_cast<Storage<T>*>(components_[std::type_index(typeid(T))])->Add(entity);
    }
    
    template <typename T>
    void RemoveComponentByEntity(Entity* entity) {
        static_cast<Storage<T>*>(components_[std::type_index(typeid(T))])->Remove(entity);
    }
    
    template <typename T>
    T* GetComponentByEntity(Entity* entity) {
        return static_cast<Storage<T>*>(components_[std::type_index(typeid(T))])->At(entity);
    }
    
private:

    std::map<boost::uuids::uuid, Entity> entities_;
    std::map<std::type_index, IStorage*> components_;
    
};

#endif