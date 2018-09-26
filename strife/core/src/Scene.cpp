#include "Scene.h"

#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>

using namespace Strife;
using namespace std;
using boost::uuids::uuid;
using nlohmann::json;

Scene::Entities::Entities(Scene* const scene) :
    scene_(scene) {};
    
const json Scene::Entities::serialize() const {
    json data;
    for (const Entity& entity : *this) {
        data.push_back(entity.id);
    }
    return data;
};

void Scene::Entities::deserialize(const json data) {
    for (const auto& entity : data) {
        add(entity.get<uuid>());
    }
};

const Entity* const Scene::Entities::add() {
    return &(*this->emplace(scene_).first);
};

const Entity* const Scene::Entities::add(const uuid id) {
    return &(*this->emplace(id, scene_).first);
};

void Scene::Entities::remove(const Entity* const entity) {
    this->erase(*entity);
};

Scene::Components::~Components() {
    for (const auto& pairTypeToStorage : *this) {
        IStorage* const storage = pairTypeToStorage.second;
        delete storage;
    }
};

const json Scene::Components::serialize() const {
    json data;
    for (const auto& pairTypeToStorage : *this) {
        const type_index type = pairTypeToStorage.first;
        const IStorage* const storage = pairTypeToStorage.second;
        const string storageIdentifier = typeToIdentifier_.at(type);
        const json storageData = storage->serialize();
        data[storageIdentifier] = storageData;
    }
    return data;
};

void Scene::Components::deserialize(json data) {
    for (json::iterator iteratorStorageIdentifierToStorageData = data.begin(); iteratorStorageIdentifierToStorageData != data.end(); iteratorStorageIdentifierToStorageData++) {
        const string storageIdentifier = iteratorStorageIdentifierToStorageData.key();
        const json storageData = iteratorStorageIdentifierToStorageData.value();
        const type_index type = identifierToType_.at(storageIdentifier);
        IStorage* const storage = this->at(type);
        storage->deserialize(storageData);
    }
};

Component* const Scene::Components::add(const type_index type, const Entity* const entity) {
    return this->at(type)->add(entity);
};

Component* const Scene::Components::add(const type_index type, const uuid id, const Entity* const entity) {
    return this->at(type)->add(id, entity);
};

void Scene::Components::remove(const type_index type, const Entity* const entity) {
    return this->at(type)->remove(entity);
};

Component* const Scene::Components::get(const type_index type, const Entity* const entity) const {
    return this->at(type)->get(entity);
};

Scene::Scene() :
    entities(this) {};

const json Scene::serialize() const {
    json data;
    data["entities"] = entities.serialize();
    data["components"] = components.serialize();
    return data;
};

void Scene::deserialize(const json data) {
    entities.deserialize(data["entities"]);
    components.deserialize(data["components"]);
};