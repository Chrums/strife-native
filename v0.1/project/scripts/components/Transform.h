#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <Eigen/Dense>
#include <Eigen/Geometry>

#include <nlohmann/json.hpp>

#include "Component.h"
#include "utility/Serialization.h"

template <typename T, int D>
class Transform : public Component, public Eigen::Transform<T, D, Eigen::Affine> {
    
public:
    
    Transform(const Transform& transform) :
        Component(transform.entity),
        Eigen::Transform<T, D, Eigen::Affine>(transform) {};
        
    Transform(Entity* entity) :
        Component(entity),
        Eigen::Transform<T, D, Eigen::Affine>(Eigen::Transform<T, D, Eigen::Affine>::Identity()) {};
        
    Transform(const boost::uuids::uuid id, Entity* entity) :
        Component(id, entity),
        Eigen::Transform<T, D, Eigen::Affine>(Eigen::Transform<T, D, Eigen::Affine>::Identity()) {};
    
    nlohmann::json serialize() {
        nlohmann::json data;
        data["data"] = Serialization::SerializeMatrix<float, 4, 4>(this->matrix());
        return data;
    };
    
    void deserialize(nlohmann::json data) {
        this->matrix() = Serialization::DeserializeMatrix<float, 4, 4>(data["data"]);
    };

};

typedef Transform<float, 2> Transform2f;
typedef Transform<float, 3> Transform3f;
typedef Transform<double, 2> Transform2d;
typedef Transform<double, 3> Transform3d;

#endif