#ifndef SCENE_H
#define SCENE_H

#include <map>

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
    T& AddComponent(Entity& entity) {
        T* component = new T(&entity);
        components_[typeid(T).hash_code()][entity.id].push_back(component);
        return *component;
    }
    
    template <typename T>
    std::optional<std::reference_wrapper<T>> GetComponent(Entity& entity) {
        std::map<boost::uuids::uuid, std::vector<Component*>> entities = components_[typeid(T).hash_code()];
        auto search = entities.find(entity.id);
        return search != entities.end() && !search->second.empty()
            ? std::optional<std::reference_wrapper<T>>(*static_cast<T*>(*search->second.begin()))
            : std::nullopt;
    }
    
    // template <typename T>
    // std::vector<std::optional<std::reference_wrapper<T>>> GetComponents(Entity& entity) {
    //     std::map<boost::uuids::uuid, std::vector<Component*>> entities = components_[typeid(T).hash_code()];
    //     auto search = entities.find(entity.id);
    //     if (search != entities.end()) {
    //         std::vector<std::optional<std::reference_wrapper<T>>> components(search->second.size());
    //         std::transform(
    //             search->second.begin(),
    //             search->second.end(),
    //             components.begin(),
    //             [=](Component* component) {
    //                 return std::optional<std::reference_wrapper<T>>(*static_cast<T*>(component));
    //             }
    //         );
    //         return components;
    //     } else {
    //         return std::vector<std::optional<std::reference_wrapper<T>>>();
    //     }
    // }
    
    // template <typename T>
    // std::vector<std::reference_wrapper<T>> GetComponents(Entity& entity) {
    //     std::map<boost::uuids::uuid, std::vector<Component*>> entities = components_[typeid(T).hash_code()];
    //     auto search = entities.find(entity.id);
    //     return search != entities.end()
    //         ? std::vector<std::reference_wrapper<T>>(std::vector<T*>(search->second.begin(), search->second.end()), std::vector<T*>(search->second.begin(), search->second.end()))
    //         : std::vector<std::reference_wrapper<T>>();
    // }
    
private:

    std::map<boost::uuids::uuid, Entity> entities_;
    std::map<size_t, std::map<boost::uuids::uuid, std::vector<Component*>>> components_;
    
};

#endif