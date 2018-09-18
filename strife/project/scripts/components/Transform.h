#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <Eigen/Dense>
#include <Eigen/Geometry>

#include <nlohmann/json.hpp>

#include "Component.h"

class Transform : public Component {
    
public:
    
    Transform(const Transform& transform);
    Transform(Entity* entity);
    Transform(const boost::uuids::uuid id, Entity* entity);
    
    nlohmann::json serialize();
    void deserialize(nlohmann::json data);

    Eigen::Vector3f position();
    
    template <typename T>
    Transform& translate(const Eigen::MatrixBase<T> translation) {
        data_.translate(translation);
        return *this;
    };
    
    Eigen::Quaternionf rotation();

private:

    Eigen::Affine3f data_;

};

#endif