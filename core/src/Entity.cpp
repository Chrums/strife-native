#include "Entity.h"

#include <algorithm>
#include <numeric>

#include "Scene.h"

using namespace std;
using boost::uuids::uuid;

Entity::Entity(const Entity& entity) :
    Unique(entity.id),
    scene_(entity.scene_) {};
    
Entity::Entity(Scene* scene) :
    scene_(scene) {};
    
Entity::Entity(const uuid id, Scene* scene) :
    Unique(id),
    scene_(scene) {};

Component* Entity::addComponent(type_index type) {
    return scene_->addComponent(type, this);
};

void Entity::removeComponent(type_index type) {
    scene_->removeComponent(type, this);
};

Component* Entity::getComponent(type_index type) {
    return scene_->getComponent(type, this);
};