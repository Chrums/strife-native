#include "Entity.h"

#include <algorithm>
#include <numeric>

#include "Scene.h"

Entity::Entity(const Entity& entity) :
    Unique(entity.id),
    scene_(entity.scene_),
    parentId_(entity.parentId_),
    childrenIds_(entity.childrenIds_) {};
    
Entity::Entity(Scene* scene) :
    scene_(scene) {}
    
Entity::Entity(const boost::uuids::uuid id, Scene* scene) :
    Unique(id),
    scene_(scene) {}
    
Entity* Entity::GetParent(void) {
    return parentId_
        ? scene_->GetEntityById(parentId_.value())
        : nullptr;
}

void Entity::SetParent(Entity* entity) {
    parentId_ = entity->id;
}

std::vector<Entity*> Entity::GetChildren(void) {
    return std::reduce(
        childrenIds_.begin(),
        childrenIds_.end(),
        std::vector<Entity*>(),
        [=](std::vector<Entity*> state, boost::uuids::uuid childId) {
            Entity* child = scene_->GetEntityById(childId);
            if (child != nullptr) state.push_back(child);
            return state;
        }
    );
}

void Entity::AddChild(Entity* entity) {
    childrenIds_.insert(entity->id);
}

void Entity::RemoveChild(Entity* entity) {
    childrenIds_.erase(entity->id);
}

Component* Entity::AddComponentByType(std::type_index type) {
    return scene_->AddComponentByTypeAndEntity(type, this);
}

void Entity::RemoveComponentByType(std::type_index type) {
    scene_->RemoveComponentByTypeAndEntity(type, this);
}

Component* Entity::GetComponentByType(std::type_index type) {
    return scene_->GetComponentByTypeAndEntity(type, this);
}