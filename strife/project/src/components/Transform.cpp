#include "components/Transform.h"

#include "utility/Math.h"

#include <iostream>

using namespace std;
using nlohmann::json;

Transform::Transform(const Transform& transform) :
    Component(transform.entity),
    position(transform.position),
    rotation(transform.rotation),
    scale(transform.scale) {};

Transform::Transform(Entity* entity) :
    Component(entity),
    position(Eigen::Vector3f::Zero()),
    rotation(Eigen::Quaternionf::Identity()),
    scale(Eigen::Vector3f::Ones()) {};

json Transform::serialize() {
    json data;
    
    data["position"] = serializeMatrix(position);
    data["rotation"] = serializeQuaternion(rotation);
    data["scale"] = serializeMatrix(scale);
    
    return data;
}

void Transform::deserialize(json data) {
    
    position = deserializeMatrix<float, 1, 3>(data["position"]);
    rotation = deserializeQuaternion<float>(data["rotation"]);
    scale = deserializeMatrix<float, 1, 3>(data["scale"]);
    
}