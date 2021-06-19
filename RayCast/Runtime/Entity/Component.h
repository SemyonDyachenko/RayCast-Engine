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
#include "../Light/LightPoint.h"
#include "../Light/DirectionalLight.h"

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
	AnimationComponent(AnimatedModel& model,Animator & animator) : model(model),animator(animator){}

	void AddAnimation(std::string name,Animation& animation) {}
	void SetAnimation(std::string name) {}
};


class MeshComponent : public Component{ 
public:

	Mesh mesh;
	glm::vec3 color;

	MeshComponent() = default;
	MeshComponent(const MeshComponent&) = default;
	MeshComponent(Mesh& mesh, glm::vec3& color) : mesh(mesh), color(color) { this->mesh.SetSolidColor(this->color); }

	void SetColor() {
		this->mesh.SetSolidColor(this->color);
	}
};

class TagComponent : public Component {
public:
	std::string tag;

	TagComponent() = default;
	TagComponent(const TagComponent&) = default;
	TagComponent(std::string& tag) : tag(tag) { }
};

class CircleColliderComponent : public Component {
public:
	CircleColliderComponent() = default;
	CircleColliderComponent(const CircleColliderComponent&) = default;

};

class BoxColliderComponent : public Component {
public:
	BoxColliderComponent() = default;
	BoxColliderComponent(const BoxColliderComponent&) = default;

};

class RigidBodyComponent : public Component {
public:
	RigidBodyComponent() = default;
	RigidBodyComponent(const RigidBodyComponent&) = default;

};

class DirectionalLightComponent : public Component {
public:
	DirectionalLight light;
	DirectionalLightComponent() = default;
	DirectionalLightComponent(const DirectionalLightComponent&) = default;
	DirectionalLightComponent(DirectionalLight& light) : light(light) {}
};

class LightPointComponent : public Component {
public:
	LightPoint light;
	glm::vec3 position;
	LightPointComponent() = default;
	LightPointComponent(const LightPointComponent&) = default;
	LightPointComponent(LightPoint& light, glm::vec3 position) : light(light), position(position) { light.SetPosition(this->position); }
};