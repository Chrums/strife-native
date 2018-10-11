#ifndef MATH_H
#define MATH_H

#include <nlohmann/json.hpp>

#include <Eigen/Dense>
#include <Eigen/Geometry>

namespace Serialization {

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

}  // namespace Serialization

#endif
