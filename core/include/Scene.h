#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <map>
#include <numeric>
#include <typeindex>
#include <typeinfo>
#include <vector>

#include "Entity.h"
#include "Component.h"

class Scene {
    
public:

    Scene(void);
    
    Entity& AddEntity(void);
    Entity& AddEntity(Entity& parent);
    Entity& AddEntity(boost::uuids::uuid id, Entity& parent);
    void RemoveEntity(Entity& entity);
    void MoveEntity(Entity& entity, Entity& target);
    std::optional<std::reference_wrapper<Entity>> GetEntityById(const boost::uuids::uuid id);
    
    template <typename T>
    T& AddComponentByEntity(Entity& entity) {
        T* component = new T(&entity);
        components_[std::type_index(typeid(T))][entity.id].push_back(component);
        return *component;
    }
    
    template <typename T>
    std::optional<std::reference_wrapper<T>> GetComponentByEntity(Entity& entity) {
        std::map<boost::uuids::uuid, std::vector<Component*>> entities = components_[std::type_index(typeid(T))];
        auto search = entities.find(entity.id);
        return search != entities.end() && !search->second.empty()
            ? std::optional<std::reference_wrapper<T>>(*static_cast<T*>(*search->second.begin()))
            : std::nullopt;
    }
    
    template <typename T>
    std::vector<std::reference_wrapper<T>> GetComponentsByEntity(Entity& entity) {
        std::map<boost::uuids::uuid, std::vector<Component*>> entities = components_[std::type_index(typeid(T))];
        auto search = entities.find(entity.id);
        return search != entities.end()
            ? std::reduce(
                search->second.begin(),
                search->second.end(),
                std::vector<std::reference_wrapper<T>>(),
                [=](std::vector<std::reference_wrapper<T>> state, Component* component) {
                    state.push_back(*static_cast<T*>(component));
                    return state;
                }
            )
            : std::vector<std::reference_wrapper<T>>();
    }
    
private:

    std::map<boost::uuids::uuid, Entity> entities_;
    std::map<std::type_index, std::map<boost::uuids::uuid, std::vector<Component*>>> components_;
    
};

#endif