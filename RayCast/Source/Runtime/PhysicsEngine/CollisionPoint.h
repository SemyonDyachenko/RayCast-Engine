#pragma once

#include <glm.hpp>
#include <gtx/quaternion.hpp>

struct CollisionPoints {
	glm::vec3 A;
	glm::vec3 B;
	glm::vec3 Normal;
	float Depth;
	bool HasCollision;
};

struct Transform {
	glm::vec3 Position;
	glm::quat Rotation;
	glm::vec3 Scale;
};

