#include "Entity.h"

#include <algorithm>
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "Scene.h"

using namespace Strife;
using namespace std;
using boost::uuids::uuid;
using nlohmann::json;

Entity::Entity(const Entity& entity) :
    Unique(entity),
    Hierarchy(entity),
    scene(entity.scene) {};

Entity::Entity(Scene* scene) :
    Unique(Unique::RandomGenerator()),
    scene(scene) {};
    
Entity::Entity(const boost::uuids::uuid id, Scene* scene) :
    Unique(id),
    scene(scene) {};
    
void Entity::setParent(Entity* const parent) {
    const uuid parentId = parent->id;
    Hierarchy::setParent(parentId);
}

Entity* const Entity::getParent() const {
    std::optional<uuid> parentIdOpt = Hierarchy::getParent();
    if (parentIdOpt) {
        const uuid parentId = parentIdOpt.value();
        return scene->getEntity(parentId);
    } else {
        return nullptr;
    }
}

void Entity::addChild(const Entity* const child) {
    const uuid childId = child->id;
    Hierarchy::addChild(childId);
}

void Entity::removeChild(const Entity* const child) {
    const uuid childId = child->id;
    Hierarchy::removeChild(childId);
}

const set<Entity*> Entity::getChildren() const {
    const set<uuid> childrenIds = Hierarchy::getChildren();
    return accumulate(
        childrenIds.begin(),
        childrenIds.end(),
        set<Entity*>(),
        [=](set<Entity*> state, const uuid childId) {
            state.insert(scene->getEntity(childId));
            return state;
        }
    );
}