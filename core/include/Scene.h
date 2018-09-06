#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <map>
#include <numeric>
#include <typeindex>
#include <typeinfo>
#include <vector>

#include <boost/property_tree/ptree.hpp>

#include "Component.h"
#include "Delegate.h"
#include "Entity.h"
#include "System.h"

class Scene {
    
public:
    
    Delegate<void(void)> update;
    Delegate<void(void)> render;
    
    void Initialize(void);
    void Update(void);
    void Render(void);
    
    // boost::property_tree::ptree Serialize(void);
    void Deserialize(boost::property_tree::ptree data);
    
    Entity* AddEntity(void);
    Entity* AddEntity(boost::uuids::uuid);
    void RemoveEntity(Entity* entity);
    Entity* GetEntityById(const boost::uuids::uuid id);
    
    Component* AddComponentByTypeAndEntity(std::type_index type, Entity* entity);
    void RemoveComponentByTypeAndEntity(std::type_index type, Entity* entity);
    Component* GetComponentByTypeAndEntity(std::type_index type, Entity* entity);
    
    template <typename T>
    void Register(std::string identifier) {
        std::type_index type = std::type_index(typeid(T));
        systems_[type] = new System<T>(this);
        identifierToType_.insert({ identifier, type });
        typeToIdentifier_.insert({ type, identifier });
    };
    
    template <typename S, typename T>
    void Register() {
        systems_[std::type_index(typeid(T))] = new S(this);
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
    
    std::map<std::string, std::type_index> identifierToType_;
    std::map<std::type_index, std::string> typeToIdentifier_;
    
};

#endif