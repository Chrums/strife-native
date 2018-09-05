#include "Scene.h"

void Scene::Initialize(void) {
    for (auto& it : systems_) {
        it.second->Initialize();
    }
}

void Scene::Update(void) {
    for (auto& it : systems_) {
        it.second->Update();
    }
}

void Scene::Render(void) {
    for (auto& it : systems_) {
        it.second->Render();
    }
}

Entity* Scene::AddEntity(void) {
    Entity temp(this);
    entities_.insert({ temp.id, temp });
    return &entities_.find(temp.id)->second;
};

Entity* Scene::AddEntity(Entity* parent) {
    Entity temp(this);
    entities_.insert({ temp.id, temp });
    Entity* entity = &entities_.find(temp.id)->second;
    parent->AddChild(entity);
    entity->SetParent(parent);
    return entity;
};

Entity* Scene::AddEntity(boost::uuids::uuid id, Entity* parent) {
    Entity temp(id, this);
    entities_.insert({ temp.id, temp });
    Entity* entity = &entities_.find(temp.id)->second;
    parent->AddChild(entity);
    entity->SetParent(parent);
    return entity;
};

void Scene::RemoveEntity(Entity* entity) {
    
    // Recursively remove all children
    std::vector<Entity*> children = entity->GetChildren();
    std::for_each(children.begin(), children.end(), [=](Entity* child) {
        this->RemoveEntity(child);
    });
    
    // Remove entity as child of parent
    Entity* parent = entity->GetParent();
    if (parent != nullptr) {
        parent->RemoveChild(entity);
    }
    
    // Remove entity from scene
    entities_.erase(entity->id);
    
    // TODO: Remove all components...
    
};

void Scene::MoveEntity(Entity* entity, Entity* target) {
    Entity* parent = entity->GetParent();
    if (parent != nullptr) {
        parent->RemoveChild(entity);
    }
    entity->SetParent(target);
    target->AddChild(entity);
};

Entity* Scene::GetEntityById(const boost::uuids::uuid id) {
    auto search = entities_.find(id);
    return search != entities_.end()
        ? &search->second
        : nullptr;
};

Component* Scene::AddComponentByTypeAndEntity(std::type_index type, Entity* entity) {
    return systems_[type]->Add(entity);
};

void Scene::RemoveComponentByTypeAndEntity(std::type_index type, Entity* entity) {
    systems_[type]->Remove(entity);
};

Component* Scene::GetComponentByTypeAndEntity(std::type_index type, Entity* entity) {
    return systems_[type]->At(entity);
};