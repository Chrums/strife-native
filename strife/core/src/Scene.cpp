#include "Scene.h"

#include <boost/uuid/uuid_io.hpp>
#include "Unique.h"

using namespace Strife;
using namespace std;
using boost::uuids::uuid;

Scene::Entities::Entities(Scene* const scene) :
    scene_(scene) {};

const Entity* const Scene::Entities::add() {
    return &(*this->emplace(scene_).first);
};

const Entity* const Scene::Entities::add(const uuid id) {
    return &(*this->emplace(id, scene_).first);
};

void Scene::Entities::remove(const Entity* const entity) {
    this->erase(*entity);
};

Component* const Scene::Components::add(const type_index type, const Entity* const entity) {
    return this->at(type)->add(entity);
};

Component* const Scene::Components::add(const type_index type, const uuid id, const Entity* const entity) {
    return this->at(type)->add(id, entity);
};

void Scene::Components::remove(const type_index type, const Entity* const entity) {
    this->at(type)->remove(entity);
};

Component* const Scene::Components::get(const type_index type, const Entity* const entity) const {
    return this->at(type)->get(entity);
};

Scene::Scene() :
    entities(this) {};