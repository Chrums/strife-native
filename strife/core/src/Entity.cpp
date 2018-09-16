#include "Entity.h"

#include <iostream>
#include <string>

#include "Scene.h"

using boost::uuids::uuid;
using nlohmann::json;

Entity::Entity(const Entity& entity) :
    Unique(entity.id),
    scene(entity.scene) {};
    
Entity::Entity(Scene* scene) :
    scene(scene) {};
    
Entity::Entity(const uuid id, Scene* scene) :
    Unique(id),
    scene(scene) {};
    
json Entity::serialize() {
    json data;
    data["unique"] = Unique::serialize();
    return data;
};

void Entity::deserialize(json data) {
    Unique::deserialize(data["unique"]);
};

Component* Entity::addComponent(type_index type) {
    return scene->addComponent(type, this);
};

void Entity::removeComponent(type_index type) {
    scene->removeComponent(type, this);
};

Component* Entity::getComponent(type_index type) {
    return scene->getComponent(type, this);
};