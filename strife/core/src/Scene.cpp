#include "Scene.h"

#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>

using namespace Strife::Core;
using namespace std;
using boost::uuids::uuid;

const unsigned int Scene::EntityAdded::Priority = Dispatcher::Final;
const unsigned int Scene::EntityRemoved::Priority = Dispatcher::Final;

Scene::Entities::Entities(Scene& scene, Dispatcher& dispatcher)
    : scene_(scene)
    , dispatcher_(dispatcher) {}

const Entity Scene::Entities::add() {
    const Entity entity(scene_);
	dispatcher_.emit<EntityAdded>(entity);
	return entity;
}

void Scene::Entities::remove(const Entity& entity) {
	scene_.components.remove(entity);
	dispatcher_.emit<EntityRemoved>(entity);
}

const Entity Scene::Entities::get(const uuid id, Context& context) {
	const Entity entity = context.at(id);
	dispatcher_.emit<EntityAdded>(entity);
	return entity;
}

Scene::Components::Components(Scene& scene)
    : scene_(scene) {}

Scene::Components::~Components() {
    for (auto [type, storage] : components_) {
		delete storage;
	}
}

const Data Scene::Components::serialize() const {
	Data data;
    for (auto [type, storage] : components_) {
		const string storageIdentifier = typeToIdentifier_.at(type);
		const Data storageData = storage->serialize();
		data[storageIdentifier] = storageData;
	}
	return data;
}

void Scene::Components::deserialize(Context context) {
    for (auto& iteratorStorageIdentifierToStorageData : context.data.items()) {
		const string storageIdentifier = iteratorStorageIdentifierToStorageData.key();
		Data storageData = iteratorStorageIdentifierToStorageData.value();
		const type_index type = identifierToType_.at(storageIdentifier);
        IStorage* const storage = components_.at(type);
        storage->deserialize(context.bind(storageData));
	}
}

Component* const Scene::Components::add(const type_index type, const Entity& entity) {
	return components_.at(type)->add(entity);
}

Component* const Scene::Components::add(const type_index type, const uuid id, const Entity& entity) {
	return components_.at(type)->add(id, entity);
}

void Scene::Components::remove(const type_index type, const Entity& entity) {
	return components_.at(type)->remove(entity);
}

void Scene::Components::remove(const Entity& entity) {
	for (const auto& pairTypeToStorage : components_) {
		IStorage* const storage = pairTypeToStorage.second;
		storage->remove(entity);
	}
}

IStorage* const Scene::Components::get(const type_index type) const {
	return components_.at(type);
}

Component* const Scene::Components::get(const type_index type, const Entity& entity) const {
	return components_.at(type)->get(entity);
}

const std::map<const type_index, IStorage* const>& Scene::Components::get() const {
    return components_;
}

string Scene::Components::identifier(type_index type) {
    return typeToIdentifier_.at(type);
}

type_index Scene::Components::type(string type) {
    return identifierToType_.at(type);
}

Scene::Systems::Systems(Scene& scene, Dispatcher& dispatcher)
    : scene_(scene)
    , dispatcher_(dispatcher) {}

Scene::Systems::~Systems() {
	for (const auto& pairTypeToSystem : systems_) {
		ISystem* const system = pairTypeToSystem.second;
		delete system;
	}
}

Scene::Scene()
    : entities(*this, dispatcher)
    , components(*this)
    , systems(*this, dispatcher) {}

const Data Scene::serialize() const {
	Data data;
	data["components"] = components.serialize();
	return data;
}

void Scene::deserialize(Data data) {
	Context context(*this);
	Data componentsData = data["components"];
    components.deserialize(context.bind(componentsData));
}
