#include "Transform.h"

Transform::Transform(Entity* entity) :
    Component(entity),
    position(0),
    orientation(0),
    scale(1) {}