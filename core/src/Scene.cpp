#include "Scene.h"

using namespace Strife::Core;
using namespace std;
using boost::uuids::uuid;

Scene::Entities::Entities(Scene& scene)
    : scene_(scene) {}

const Entity Scene::Entities::add() {
    const Entity entity(scene_);
	return entity;
}

void Scene::Entities::remove(const Entity entity) {
	scene_.components.remove(entity);
}

Scene::Components::Components(Scene& scene)
    : scene_(scene) {}
    
Scene::Components::~Components() {
    for (auto [type, storage] : components_) {
		delete storage;
	}
}

Component& Scene::Components::add(const type_index type, const Entity entity) {
	return components_.at(type)->add(entity);
}

Component& Scene::Components::add(const type_index type, const uuid id, const Entity entity) {
	return components_.at(type)->add(id, entity);
}

void Scene::Components::remove(const type_index type, const Entity entity) {
	return components_.at(type)->remove(entity);
}

void Scene::Components::remove(const Entity entity) {
	for (auto [type, storage] : components_) {
		storage->remove(entity);
	}
}

Component& Scene::Components::get(const type_index type, const Entity entity) const {
	return components_.at(type)->get(entity);
}

IStorage& Scene::Components::get(const type_index type) const {
	return *components_.at(type);
}

Component* const Scene::Components::find(const type_index type, const Entity entity) const {
    return components_.at(type)->find(entity);
}

Scene::Scene()
    : entities(*this)
    , components(*this) {}