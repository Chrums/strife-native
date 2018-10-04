#include "Component.h"

using namespace Strife::Core;
using boost::uuids::uuid;

Component::Component(const Entity& entity) :
    entity(entity),
    scene(*entity.scene) {};

Component::Component(const uuid id, const Entity& entity) :
    Unique(id),
    entity(entity),
    scene(*entity.scene) {};

const Data Component::serialize() const {
    return Data();
};

void Component::deserialize(const Data data) {};

Component::~Component() {};
