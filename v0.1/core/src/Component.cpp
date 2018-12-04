#include "Component.h"

using namespace Strife::Core;
using boost::uuids::uuid;

Component::Component(const Entity& entity)
    : entity(entity) {}

Component::Component(const uuid id, const Entity& entity)
    : Unique(id)
    , entity(entity) {}