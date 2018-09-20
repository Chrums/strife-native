#ifndef SCENE_H
#define SCENE_H

#include <map>
#include <typeindex>
#include <vector>

#include <nlohmann/json.hpp>

#include "Component.h"
#include "Delegate.h"
#include "Entity.h"
#include "System.h"

class Scene {
    
public:
    
    Delegate<void(void)> updates;
    Delegate<void(void)> renders;
    
    ~Scene();
    
    nlohmann::json serialize();
    void deserialize(nlohmann::json data);
    
    void initialize();
    void update();
    void render();
    
    Entity* addEntity();
    Entity* addEntity(const boost::uuids::uuid id);
    void removeEntity(Entity* entity);
    Entity* getEntity(const boost::uuids::uuid id);
    void moveEntity(Entity* entity, Entity* target);
    
    Component* addComponent(std::type_index type, Entity* entity);
    void removeComponent(std::type_index type, Entity* entity);
    Component* getComponent(std::type_index type, Entity* entity);
    
    template <typename T>
    void initialize(std::string identifier) {
        std::type_index type = std::type_index(typeid(T));
        systems_[type] = new System<T>(this);
        identifierToType_.insert({ identifier, type });
        typeToIdentifier_.insert({ type, identifier });
    };
    
    template <typename S, typename T>
    void initialize(std::string identifier) {
        std::type_index type = std::type_index(typeid(T));
        systems_[type] = new S(this);
        identifierToType_.insert({ identifier, type });
        typeToIdentifier_.insert({ type, identifier });
    }
    
    template <typename T>
    T* addComponent(Entity* entity) {
        return static_cast<System<T>*>(systems_[std::type_index(typeid(T))])->Add(entity);
    };
    
    template <typename T>
    void removeComponent(Entity* entity) {
        static_cast<System<T>*>(systems_[std::type_index(typeid(T))])->Remove(entity);
    };
    
    template <typename T>
    T* getComponent(Entity* entity) {
        return static_cast<System<T>*>(systems_[std::type_index(typeid(T))])->At(entity);
    };
    
private:

    std::map<boost::uuids::uuid, Entity> entities_;
    std::map<std::type_index, ISystem*> systems_;
    
    std::map<std::string, std::type_index> identifierToType_;
    std::map<std::type_index, std::string> typeToIdentifier_;
    
};

#endif