#include "Transform.h"

Transform::Transform(const Transform& transform) :
    Component(transform.entity_),
    position(transform.position),
    orientation(transform.orientation),
    scale(transform.scale) {}

Transform::Transform(Entity* entity) :
    Component(entity),
    position(0),
    orientation(0),
    scale(1) {}
