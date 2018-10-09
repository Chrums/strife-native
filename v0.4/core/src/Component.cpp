#include "Component.h"

using namespace Strife::Core;
using boost::uuids::uuid;

template <class C>
void Component::AssertBase() {
    static_assert(
        std::is_base_of<Component, C>::value,
        "Type not derived from Component"
    );
};

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
