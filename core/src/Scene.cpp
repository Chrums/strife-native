#include "Scene.h"

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>

using namespace std;
using nlohmann::json;
using boost::uuids::uuid;

Scene::~Scene() {
    for (auto& pairSystemTypeToSystem : systems_) {
        ISystem* system = pairSystemTypeToSystem.second;
        delete system;
    }
}

void Scene::initialize(void) {
    
}

void Scene::update() {
    updates();
}

void Scene::render() {
    renders();
}

json Scene::serialize() {
    json data;
    
    json entityArray;
    for (auto& pairEntityIdToEntity : entities_) {
        uuid entityId = pairEntityIdToEntity.first;
        Entity* entity = &pairEntityIdToEntity.second;
        entityArray.push_back(boost::lexical_cast<string>(entityId));
    }
    data["entities"] = entityArray;
    
    json systemMap;
    for (auto& pairSystemTypeToSystem : systems_) {
        type_index systemType = pairSystemTypeToSystem.first;
        ISystem* system = pairSystemTypeToSystem.second;
        string systemIdentifier = typeToIdentifier_.at(systemType);
        systemMap[systemIdentifier] = system->serialize(entities_);
    }
    data["systems"] = systemMap;
    
    return data;
}

void Scene::deserialize(json data) {
    
    json entityArray = data["entities"];
    for (auto& entityIdData : entityArray) {
        string entityId = entityIdData.get<string>();
        addEntity(boost::lexical_cast<uuid>(entityId));
    }
    
    json systemMap = data["systems"];
    for (json::iterator iteratorSystemIdentifierToSystemData = systemMap.begin(); iteratorSystemIdentifierToSystemData != systemMap.end(); iteratorSystemIdentifierToSystemData++) {
        string systemIdentifier = iteratorSystemIdentifierToSystemData.key();
        json systemData = iteratorSystemIdentifierToSystemData.value();
        type_index systemType = identifierToType_.at(systemIdentifier);
        ISystem* system = systems_.at(systemType);
        system->deserialize(entities_, systemData);
    }
    
}

Entity* Scene::addEntity() {
    Entity temp(this);
    entities_.insert({ temp.id, temp });
    return &entities_.find(temp.id)->second;
};

Entity* Scene::addEntity(const uuid id) {
    Entity temp(id, this);
    entities_.insert({ temp.id, temp });
    return &entities_.find(temp.id)->second;
};

void Scene::removeEntity(Entity* entity) {
    entities_.erase(entity->id);
    for (auto it : systems_) {
        it.second->remove(entity);
    }
};

Entity* Scene::getEntity(const uuid id) {
    auto search = entities_.find(id);
    return search != entities_.end()
        ? &search->second
        : nullptr;
};

Component* Scene::addComponent(std::type_index type, Entity* entity) {
    return systems_[type]->add(entity);
};

void Scene::removeComponent(std::type_index type, Entity* entity) {
    systems_[type]->remove(entity);
};

Component* Scene::getComponent(std::type_index type, Entity* entity) {
    return systems_[type]->at(entity);
};