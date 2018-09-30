#ifndef SYSTEM_H
#define SYSTEM_H

#include <iterator>
#include <map>
#include <string>

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <nlohmann/json.hpp>

#include "Component.h"
#include "Entity.h"

class Scene;

class ISystem {
    
public:
    
    ISystem(Scene* scene) :
        scene_(scene) {};
    
    virtual ~ISystem() {};
    
    virtual void initialize() = 0;
    virtual nlohmann::json serialize(std::map<boost::uuids::uuid, Entity>& entities) = 0;
    virtual void deserialize(std::map<boost::uuids::uuid, Entity>& entities, nlohmann::json data) = 0;

    virtual Component* add(Entity* entity) = 0;
    virtual void remove(Entity* entity) = 0;
    virtual Component* at(Entity* entity) = 0;
    
protected:
    Scene* scene_;
    
};

template <typename T>
class System : public ISystem {
    
public:

    System(Scene* scene) :
        ISystem(scene) {};
    
    void initialize() {
        
    };
    
    nlohmann::json serialize(std::map<boost::uuids::uuid, Entity>& entities) {
        nlohmann::json data;
        for (auto& pairEntityIdToComponent : components_) {
            boost::uuids::uuid entityId = pairEntityIdToComponent.first;
            T& component = pairEntityIdToComponent.second;
            nlohmann::json componentPair;
            componentPair["id"] = boost::lexical_cast<std::string>(component.id);
            componentPair["data"] = component.serialize();
            data[boost::lexical_cast<std::string>(entityId)] = componentPair;
        }
        return data;
    }
    
    void deserialize(std::map<boost::uuids::uuid, Entity>& entities, nlohmann::json data) {
        for (nlohmann::json::iterator iteratorEntityIdToComponentPair = data.begin(); iteratorEntityIdToComponentPair != data.end(); iteratorEntityIdToComponentPair++) {
            std::string entityId = iteratorEntityIdToComponentPair.key();
            nlohmann::json componentPair = iteratorEntityIdToComponentPair.value();
            std::string componentId = componentPair["id"].get<std::string>();
            nlohmann::json componentData = componentPair["data"];
            Entity* entity = &entities.at(boost::lexical_cast<boost::uuids::uuid>(entityId));
            Component* component = add(boost::lexical_cast<boost::uuids::uuid>(componentId), entity);
            component->deserialize(componentData);
        }
    }
    
    void update() {
        
    };
    
    void render() {
        
    };
    
    T* add(Entity* entity) {
        return &components_.emplace(entity->id, entity).first->second;
    };
    
    T* add(const boost::uuids::uuid id, Entity* entity) {
        return &components_.try_emplace(entity->id, id, entity).first->second;
    }
    
    void remove(Entity* entity) {
        components_.erase(entity->id);
    };
    
    T* at(Entity* entity) {
        return &components_.at(entity->id);
    };
    
protected:
    
    std::map<boost::uuids::uuid, T> components_;
    
};

#endif