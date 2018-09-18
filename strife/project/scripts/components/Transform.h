#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <Eigen/Dense>
#include <Eigen/Geometry>

#include <nlohmann/json.hpp>

#include "Component.h"

class Transform : public Component {
    
public:

    Eigen::Vector3f position;
    Eigen::Quaternionf rotation;
    Eigen::Vector3f scale;
    
    Transform(const Transform& transform);
    Transform(Entity* entity);
    Transform(const boost::uuids::uuid id, Entity* entity);
    
    nlohmann::json serialize();
    void deserialize(nlohmann::json data);
    
};

#endif