#pragma once

#include <glm.hpp>

#include <gtx/quaternion.hpp>

class BoxCollider
{
public:
	virtual ~BoxCollider() = default;

public:
	glm::vec3 Size;
	glm::vec3 Position;
	glm::quat Rotation;
};

