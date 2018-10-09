#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <string>

#include <Eigen/Dense>
#include <Eigen/Geometry>

#include <nlohmann/json.hpp>

#include "Component.h"
#include "Entity.h"
#include "utility/Serialization.h"

template <typename T, int D>
class Transform : public Strife::Core::Component, public Eigen::Transform<T, D, Eigen::Affine> {

public:

    static void initialize(Strife::Core::System<Transform>& system) {}

    static const std::string Identifier;

    Transform(const Transform& transform) :
        Component(transform.entity),
        Eigen::Transform<T, D, Eigen::Affine>(transform) {};

    Transform(const Strife::Core::Entity& entity) :
        Component(entity),
        Eigen::Transform<T, D, Eigen::Affine>(Eigen::Transform<T, D, Eigen::Affine>::Identity()) {};

    Transform(const boost::uuids::uuid id, const Strife::Core::Entity& entity) :
        Component(id, entity),
        Eigen::Transform<T, D, Eigen::Affine>(Eigen::Transform<T, D, Eigen::Affine>::Identity()) {};

    const nlohmann::json serialize() const {
        nlohmann::json data;
        data["data"] = Serialization::SerializeMatrix<T, D+1, D+1>(this->matrix());
        return data;
    };

    void deserialize(nlohmann::json data) {
        this->matrix() = Serialization::DeserializeMatrix<T, D+1, D+1>(data["data"]);
    };

};

typedef Transform<float, 2> Transform2f;
typedef Transform<float, 3> Transform3f;
typedef Transform<double, 2> Transform2d;
typedef Transform<double, 3> Transform3d;

#endif
