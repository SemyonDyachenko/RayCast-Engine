#pragma once

#ifndef MATH_H
#define MATH_H


#include <glm.hpp>

namespace RayCast {

	bool DecomposeModelMatrix(const glm::mat4& in_matrix, glm::vec3& outPosition, glm::vec3& outRotation, glm::vec3& outScaling);


}


#endif