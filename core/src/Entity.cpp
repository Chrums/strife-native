#include "Entity.h"

#include <algorithm>
#include <numeric>

#include "Scene.h"

using namespace std;
using boost::uuids::uuid;

Entity::Entity(const Entity& entity) :
    Unique(entity.id),
    scene(entity.scene) {};
    
Entity::Entity(Scene* scene) :
    scene(scene) {};
    
Entity::Entity(const uuid id, Scene* scene) :
    Unique(id),
    scene(scene) {};

Component* Entity::addComponent(type_index type) {
    return scene->addComponent(type, this);
};

void Entity::removeComponent(type_index type) {
    scene->removeComponent(type, this);
};

Component* Entity::getComponent(type_index type) {
    return scene->getComponent(type, this);
};