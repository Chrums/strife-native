#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"

class Transform : public Component {
public:
    Transform(const Transform& transform);
    Transform(Entity& entity);
    int position;
    int orientation;
    int scale;
};

#endif