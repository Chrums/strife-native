#include "components/Transform.h"

#include <iostream>

#include "utility/Serialization.h"

using namespace std;
using boost::uuids::uuid;
using nlohmann::json;

Transform::Transform(const Transform& transform) :
    Component(transform.entity),
    data_(transform.data_) {};

Transform::Transform(Entity* entity) :
    Component(entity),
    data_(Eigen::Affine3f::Identity()) {};
    
Transform::Transform(const uuid id, Entity* entity) :
    Component(id, entity),
    data_(Eigen::Affine3f::Identity()) {
        translate(Eigen::Vector3f(1.0f, 2.0f, 3.0f));
        cout << position() << endl;
    };

json Transform::serialize() {
    json data;
    data["data"] = Eigen::SerializeMatrix<float, 4, 4>(data_.matrix());
    return data;
}

void Transform::deserialize(json data) {
    data_.matrix() = Eigen::DeserializeMatrix<float, 4, 4>(data["data"]);
}

Eigen::Vector3f Transform::position() {
    return data_.translation();
}

Eigen::Quaternionf Transform::rotation() {
    return Eigen::Quaternionf(data_.rotation());
}