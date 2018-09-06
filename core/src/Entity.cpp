#include "Entity.h"

#include <algorithm>
#include <numeric>

#include "Scene.h"

Entity::Entity(const Entity& entity) :
    Unique(entity.id),
    scene_(entity.scene_) {};
    
Entity::Entity(Scene* scene) :
    scene_(scene) {};
    
Entity::Entity(const boost::uuids::uuid id, Scene* scene) :
    Unique(id),
    scene_(scene) {};

Component* Entity::AddComponentByType(std::type_index type) {
    return scene_->AddComponentByTypeAndEntity(type, this);
};

void Entity::RemoveComponentByType(std::type_index type) {
    scene_->RemoveComponentByTypeAndEntity(type, this);
};

Component* Entity::GetComponentByType(std::type_index type) {
    return scene_->GetComponentByTypeAndEntity(type, this);
};