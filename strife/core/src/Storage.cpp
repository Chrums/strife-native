#include "Storage.h"
#include "Scene.h"

using namespace Strife::Core;
using namespace std;
using namespace boost::uuids;

Entity Strife::Core::addEntity(Scene& scene, uuid id, EntityMap& entityMap) {
    return scene.entities.add(id, entityMap);
}
