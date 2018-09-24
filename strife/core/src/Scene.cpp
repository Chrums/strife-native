#include "Scene.h"

#include <boost/uuid/uuid_io.hpp>
#include "Unique.h"

using namespace Strife;
using namespace std;
using boost::uuids::uuid;
using nlohmann::json;

const Entity* const Scene::addEntity() {
    return &(*entities_.emplace(this).first);
};

const Entity* const Scene::addEntity(const uuid id) {
    return &(*entities_.emplace(id, this).first);
};

void Scene::removeEntity(const Entity* const entity) {
    entities_.erase(*entity);
};