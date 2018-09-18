// #include "components/Transform.h"

// #include <iostream>

// #include "utility/Serialization.h"

// using namespace std;
// using boost::uuids::uuid;
// using nlohmann::json;

// Transform::Transform(const Transform& transform) :
//     Component(transform.entity) {};

// Transform::Transform(Entity* entity) :
//     Component(entity) {};
    
// Transform::Transform(const uuid id, Entity* entity) :
//     Component(id, entity) {};

// json Transform::serialize() {
//     json data;
//     data["data"] = Eigen::SerializeMatrix<float, 4, 4>(*this);
//     return data;
// }

// void Transform::deserialize(json data) {
//     this->matrix() = Eigen::DeserializeMatrix<float, 4, 4>(data["data"]);
// }