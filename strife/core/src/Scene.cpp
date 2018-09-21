#include "Scene.h"

#include <boost/uuid/uuid_io.hpp>
#include "Unique.h"

using namespace Strife;
using namespace std;
using boost::uuids::uuid;
using nlohmann::json;

Entity* const Scene::addEntity() {
    Entity entity(this);
    entities_.insert({ entity.id, entity });
    return &entities_.find(entity.id)->second;
};

Entity* const Scene::addEntity(const uuid id) {
    Entity entity(id, this);
    entities_.insert({ entity.id, entity });
    return &entities_.find(entity.id)->second;
};

void Scene::removeEntity(const Entity* const entity) {
    
    Entity* const parent = entity->getParent();
    if (parent != nullptr) {
        parent->removeChild(entity);
    }
    
    const set<Entity*> children = entity->getChildren();
    for (Entity* child : children) {
        if (child != nullptr) {
            removeEntity(entity);
        }
    }
    
    // for (auto pairSystemTypeToSystem : systems_) {
    //     pairSystemTypeToSystem.second->remove(entity);
    // }
    
    entities_.erase(entity->id);
    
};

Entity* const Scene::getEntity(const uuid id) const {
    auto search = entities_.find(id);
    return search != entities_.end()
        ? const_cast<Entity*>(&search->second)
        : nullptr;
};

void Scene::moveEntity(Entity* const entity, Entity* const target) {
    entity->move(target);
}