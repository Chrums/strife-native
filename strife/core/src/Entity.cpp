#include "Entity.h"

#include <iostream>
#include <string>

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "Scene.h"

using namespace std;
using boost::uuids::uuid;
using nlohmann::json;

Entity::Entity(const Entity& entity) :
    Unique(entity.id),
    scene(entity.scene),
    parentId_(entity.parentId_),
    childrenIds_(entity.childrenIds_) {};
    
Entity::Entity(Scene* scene) :
    scene(scene),
    parentId_(Unique::NilGenerator()) {};
    
Entity::Entity(const uuid id, Scene* scene) :
    Unique(id),
    scene(scene),
    parentId_(Unique::NilGenerator()) {};
    
json Entity::serialize() {
    json data;
    
    data["parent"] = boost::lexical_cast<string>(parentId_);
    
    json childrenArray;
    for (uuid id : childrenIds_) {
        childrenArray.push_back(boost::lexical_cast<string>(id));
    }
    data["children"] = childrenArray;
    
    return data;
};

void Entity::deserialize(json data) {
    
    parentId_ = boost::lexical_cast<uuid>(data["parent"].get<string>());
    
    json childrenArray = data["children"];
    for (auto& childId : childrenArray) {
        childrenIds_.insert(boost::lexical_cast<uuid>(childId.get<string>()));
    }
    
};

void Entity::setParent(Entity* entity) {
    parentId_ = entity->id;
}

Entity* Entity::getParent() {
    return scene->getEntity(parentId_);
}

void Entity::addChild(Entity* entity) {
    childrenIds_.insert(entity->id);
}

void Entity::removeChild(Entity* entity) {
    childrenIds_.erase(entity->id);
}

set<Entity*> Entity::getChildren() {
    set<Entity*> entities;
    for (uuid id : childrenIds_) {
        Entity* entity = scene->getEntity(id);
        if (entity != nullptr) entities.insert(entity);
    }
    return entities;
}

Component* Entity::addComponent(type_index type) {
    return scene->addComponent(type, this);
};

void Entity::removeComponent(type_index type) {
    scene->removeComponent(type, this);
};

Component* Entity::getComponent(type_index type) {
    return scene->getComponent(type, this);
};