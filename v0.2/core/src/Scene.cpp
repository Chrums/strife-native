#include "Scene.h"

#include <boost/uuid/uuid_io.hpp>
#include "Unique.h"

using namespace Strife;
using namespace std;
using boost::uuids::uuid;
using nlohmann::json;

Scene::Scene() :
    entities(this) {};
    
json Scene::serialize() {
    json data;
    data["entities"] = entities.serialize();
    return data;
};

void Scene::deserialize(json data) {
    entities.deserialize(data["entities"]);
};