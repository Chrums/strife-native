#ifndef MATH_H
#define MATH_H

#include <nlohmann/json.hpp>

#include <Eigen/Dense>
#include <Eigen/Geometry>

namespace Eigen {
    
    template <typename T, int R, int C>
    nlohmann::json SerializeMatrix(Eigen::Matrix<T, R, C> matrix) {
        nlohmann::json data;
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                data.push_back(matrix(r, c));
            }
        }
        return data;
    }
    
    template <typename T, int R, int C>
    Eigen::Matrix<T, R, C> DeserializeMatrix(nlohmann::json data) {
        Eigen::Matrix<T, R, C> matrix;
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                matrix(r, c) = data[r * R + c].get<T>();
            }
        }
        return matrix;
    }
    
}

// template <typename T>
// nlohmann::json serializeQuaternion(Eigen::Quaternion<T> quaternion) {
//     nlohmann::json data = nlohmann::json::array({quaternion.x(), quaternion.y(), quaternion.z(), quaternion.w()});
//     return data;
// }

// template <typename T>
// Eigen::Quaternion<T> deserializeQuaternion(nlohmann::json data) {
//     Eigen::Quaternion<T> quaternion(data[0], data[1], data[2], data[3]);
//     return quaternion;
// }

#endif