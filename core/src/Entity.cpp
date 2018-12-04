#include "Entity.h"

#include "Scene.h"

using namespace Strife::Core;
using namespace std;
using boost::uuids::uuid;

Entity::Components::Components(Entity* entity)
    : entity_(entity) {}
    
Component& Entity::Components::add(const type_index type) {
	return entity_->scene->components.add(type, *entity_);
}

Component& Entity::Components::add(const type_index type, const uuid id) {
	return entity_->scene->components.add(type, id, *entity_);
}

void Entity::Components::remove(const type_index type) {
	entity_->scene->components.remove(type, *entity_);
}

Component& Entity::Components::get(const type_index type) const {
	return entity_->scene->components.get(type, *entity_);
}

Component* Entity::Components::find(const type_index type) const {
    return entity_->scene->components.find(type, *entity_);
}

Entity::Entity(const Entity& entity)
    : Unique(entity)
    , scene(entity.scene)
    , components(this) {}
    
Entity::Entity(Scene& scene)
    : scene(&scene)
    , components(this) {}
    
Entity::Entity(const uuid id, Scene& scene)
    : Unique(id)
    , scene(&scene)
    , components(this) {}
    
bool Entity::operator==(const Entity& entity) const {
	return id == entity.id;
}

bool Entity::operator!=(const Entity& entity) const {
	return !(id == entity.id);
}

void Entity::destroy() {
	scene->entities.remove(*this);
}