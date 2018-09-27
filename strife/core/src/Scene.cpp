#include "Scene.h"

#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>

using namespace Strife::Core;
using namespace std;
using boost::uuids::uuid;

Scene::Entities::Entities(Scene& scene) :
    scene_(scene) {};
    
const Entity Scene::Entities::add() const {
    return Entity(&scene_);
};

void Scene::Entities::remove(const Entity& entity) const {
    scene_.components.remove(entity);
};

const Entity Scene::Entities::get(const uuid id) const {
    return Entity(id, &scene_);
};

Scene::Components::Components(Scene& scene) :
    scene_(scene) {};

Scene::Components::~Components() {
    for (const auto& pairTypeToStorage : *this) {
        IStorage* const storage = pairTypeToStorage.second;
        delete storage;
    }
};

const Data Scene::Components::serialize() const {
    Data data;
    for (const auto& pairTypeToStorage : *this) {
        const type_index type = pairTypeToStorage.first;
        const IStorage* const storage = pairTypeToStorage.second;
        const string storageIdentifier = typeToIdentifier_.at(type);
        const Data storageData = storage->serialize();
        data[storageIdentifier] = storageData;
    }
    return data;
};

void Scene::Components::deserialize(const Data data) {
    for (Data::const_iterator iteratorStorageIdentifierToStorageData = data.begin(); iteratorStorageIdentifierToStorageData != data.end(); iteratorStorageIdentifierToStorageData++) {
        const string storageIdentifier = iteratorStorageIdentifierToStorageData.key();
        const Data storageData = iteratorStorageIdentifierToStorageData.value();
        const type_index type = identifierToType_.at(storageIdentifier);
        IStorage* const storage = this->at(type);
        storage->deserialize(storageData);
    }
};

Component* const Scene::Components::add(const type_index type, const Entity& entity) {
    return this->at(type)->add(entity);
};

Component* const Scene::Components::add(const type_index type, const uuid id, const Entity& entity) {
    return this->at(type)->add(id, entity);
};

void Scene::Components::remove(const type_index type, const Entity& entity) {
    return this->at(type)->remove(entity);
};

void Scene::Components::remove(const Entity& entity) {
    for (const auto& pairTypeToStorage : *this) {
        IStorage* const storage = pairTypeToStorage.second;
        storage->remove(entity);
    }
};

Component* const Scene::Components::get(const type_index type, const Entity& entity) const {
    return this->at(type)->get(entity);
};

Scene::Scene() :
    entities(*this),
    components(*this) {};

const Data Scene::serialize() const {
    Data data;
    data["components"] = components.serialize();
    return data;
};

void Scene::deserialize(const Data data) {
    components.deserialize(data["components"]);
};