#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <Eigen/Dense>
#include <Eigen/Geometry>

#include "Component.h"

class Transform : public Component {
    
public:

    Eigen::Vector3f position;
    Eigen::Quaternionf rotation;
    Eigen::Vector3f scale;
    
    Transform(const Transform& transform);
    Transform(Entity* entity);
    
};

#endif