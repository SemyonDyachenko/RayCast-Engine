#pragma once


#include <GL/glew.h>
#define ENABLE_GLM_EXPERIMENTAL
#include <gtx/quaternion.hpp>

#include <glm.hpp>
#include "../Camera/Camera.h"
#include "../Rendering/Material.h"
#include "../../Animation/AnimatedModel.h"
#include "../../Animation/Animation.h"
#include "../../Animation/Animator.h"

#define MAX_COMPONENTS 32

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "../Rendering/Mesh.h"

#include "Entity.h"

inline size_t GetComponentTypeID() {
	static size_t lastID = 0;
	return lastID++;
}

template<typename T> 
inline size_t GetComponentTypeID() noexcept {
	static size_t typeID = GetComponentTypeID();
	return typeID;	
}

class Entity;

class Component {
public:
	Entity* entity;

	virtual ~Component() {}
};


class TransformComponent : public Component {
public:

	glm::vec3 Position = { 0.0f,0.0f,0.0f };
	glm::vec3 Rotation = { 0.0f,0.0f,0.0f };
	glm::vec3 Scale = { 1.0f,1.0f,1.0f };

	TransformComponent() = default;
	TransformComponent(const TransformComponent&) = default;
	TransformComponent(const glm::vec3& position) : Position(position) {}

	glm::mat4 GetTrasnform() const {

		glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

		return glm::translate(glm::mat4(1.f), Position) * rotation * glm::scale(glm::mat4(1.0f), Scale);
	}
};

class ColorComponent : public Component {
public:

	glm::vec3 Color = { 1.0f,1.0f,1.0f };

	ColorComponent() = default;
	ColorComponent(const ColorComponent&) = default;
	ColorComponent(const glm::vec3 & color) : Color(color) {}

};

class CameraComponent : public Component  {
public:

	Camera camera;
	
	CameraComponent() = default;
	CameraComponent(const CameraComponent&) = default;
};

class MaterialComponent : public Component {
public:

	Material material;

	MaterialComponent() = default;
	MaterialComponent(const MaterialComponent&) = default;
	MaterialComponent(const Material& material) : material(material) {}

};

class AnimationComponent :  public Component{
public:

	AnimatedModel model;
	Animator animator;
	std::map<std::string, Animation> animations;

	AnimationComponent() = default;
	AnimationComponent(const AnimationComponent&) = default;
};


class MeshComponent : public Component{ 
public:

	Mesh mesh;

	MeshComponent() = default;
	MeshComponent(const MeshComponent&) = default;
	MeshComponent(Mesh& mesh) : mesh(mesh) {}
};