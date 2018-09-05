#include "Transform.h"

Transform::Transform(const Transform& transform) :
    Component(transform.entity_),
    position(transform.position),
    rotation(transform.rotation),
    scale(transform.scale) {};

Transform::Transform(Entity* entity) :
    Component(entity),
    position(Eigen::Vector3f::Zero()),
    rotation(Eigen::Quaternionf::Identity()),
    scale(Eigen::Vector3f::Ones()) {};