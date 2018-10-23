#include "EntityMap.h"
#include "Scene.h"

using namespace Strife::Core;
using namespace std;

EntityMap::EntityMap(Scene& scene, bool preserveIds)
    : scene_(scene)
    , preserveIds_(preserveIds) {}

Strife::Core::Entity Strife::Core::EntityMap::getEntity(const boost::uuids::uuid id) {
	if (preserveIds_) {
		return Entity(id, scene_);
	}
	auto uuidPair = uuidMap.find(id);

	if (uuidPair == uuidMap.end()) {
		pair<const boost::uuids::uuid, Entity>& entity = *uuidMap.try_emplace(id, scene_).first;
		return entity.second;
	}
	return uuidPair->second;
}
