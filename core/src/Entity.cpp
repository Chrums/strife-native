#include "Entity.h"

#include <algorithm>

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
    
std::optional<std::reference_wrapper<Entity>> Entity::GetParent(void) {
    return parentId_
        ? scene_->GetEntityById(parentId_.value())
        : std::nullopt;
}

void Entity::SetParent(Entity& entity) {
    parentId_ = entity.id;
}

std::vector<std::optional<std::reference_wrapper<Entity>>> Entity::GetChildren(void) {
    std::vector<std::optional<std::reference_wrapper<Entity>>> children(childrenIds_.size());
    std::transform(
        childrenIds_.begin(),
        childrenIds_.end(),
        children.begin(),
        [=](boost::uuids::uuid childId) {
            return scene_->GetEntityById(childId);
        }
    );
    return children;
}

void Entity::AddChild(Entity& entity) {
    childrenIds_.insert(entity.id);
}

void Entity::RemoveChild(Entity& entity) {
    childrenIds_.erase(entity.id);
}