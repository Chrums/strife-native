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
    scene(entity.scene) {};

Entity::Entity(Scene* scene) :
    scene(scene) {};
    
Entity::Entity(const boost::uuids::uuid id, Scene* scene) :
    Unique(id),
    scene(scene) {};
    
// Entity* const Entity::parent() const {
//     return scene->getParent(this);
// }

// const set<Entity*> Entity::children() const {
//     return scene->getChildren(this);
// }