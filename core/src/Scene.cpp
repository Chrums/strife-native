#include "Scene.h"
#include <boost/uuid/uuid_io.hpp>
#include <iostream>

Scene::Scene(void) {}

Entity& Scene::AddEntity(void) {
    Entity entity(this);
    entities_.insert({ entity.id, entity });
    return entities_.find(entity.id)->second;
}

Entity& Scene::AddEntity(Entity& parent) {
    Entity entity(this);
    entity.SetParent(parent);
    parent.AddChild(entity);
    entities_.insert({ entity.id, entity });
    return entities_.find(entity.id)->second;
}

Entity& Scene::AddEntity(boost::uuids::uuid id, Entity& parent) {
    Entity entity(id, this);
    entity.SetParent(parent);
    parent.AddChild(entity);
    entities_.insert({ entity.id, entity });
    return entities_.find(entity.id)->second;
}

void Scene::RemoveEntity(Entity& entity) {
    
    // Recursively remove all children
    std::vector<std::reference_wrapper<Entity>> children = entity.GetChildren();
    std::for_each(children.begin(), children.end(), [=](std::reference_wrapper<Entity> child) {
        this->RemoveEntity(child);
    });
    
    // Remove entity as child of parent
    std::optional<std::reference_wrapper<Entity>> parent = entity.GetParent();
    if (parent != std::nullopt) {
        parent->get().RemoveChild(entity);
    }
    
    // Remove entity from scene
    entities_.erase(entity.id);
    
}

void Scene::MoveEntity(Entity& entity, Entity& target) {
    std::optional<std::reference_wrapper<Entity>> parent = entity.GetParent();
    if (parent != std::nullopt) {
        parent->get().RemoveChild(entity);
    }
    entity.SetParent(target);
    target.AddChild(entity);
}

std::optional<std::reference_wrapper<Entity>> Scene::GetEntityById(const boost::uuids::uuid id) {
    auto search = entities_.find(id);
    return search != entities_.end()
        ? std::optional<std::reference_wrapper<Entity>>(search->second)
        : std::nullopt;
}