#pragma once


#include <GL/glew.h>
#define ENABLE_GLM_EXPERIMENTAL
#include <gtx/quaternion.hpp>

#include <glm.hpp>

#include "../Rendering/Material.h"
#include "../Animation/AnimatedModel.h"
#include "../Animation/Animation.h"
#include "../Animation/Animator.h"
#include "../Light/LightPoint.h"
#include "../Light/Light.h"
#include "../Light/DirectionalLight.h"

#define MAX_COMPONENTS 32

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "../Rendering/Mesh.h"

#include "Entity.h"
#include "../PhysicsEngine/BoxCollider.h"
#include "../PhysicsEngine/Collider.h"
#include "../PhysicsEngine/RigidBody.h"

#include "../Rendering/Terrain/Terrain.h"
#include "ScriptableEntity.h"

#include "../Rendering/Materials/PBRMaterial.h"

#include "ScriptableEntity.h"

#include "../Scripts/LuaScript.h"

#include "../Core/Game.h"


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
class ScriptableEntity;





class Component {
public:
	Entity* entity;

	virtual ~Component() {}
};


/*
class NativeScriptComponent : public Component {
public:
	ScriptableEntity* Instance = nullptr;

	ScriptableEntity* (*InstantiateScript)();
	void (*DestroyScript)(NativeScriptComponent*);

	NativeScriptComponent() = default;
	NativeScriptComponent(const NativeScriptComponent&) = default;


	template<typename T>
	void Bind() {
		InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
		DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
	}

};
*/


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

	glm::quat GetQuatRotation() {
		glm::quat rotation = glm::quat(Rotation);
		return rotation;
	}

	glm::vec3& GetPosition() { return Position; }
	glm::vec3& GetRotation() { return Rotation; }
	glm::vec3& GetScale() { return Scale; }

	void SetPosition(glm::vec3 position) { Position = position; }
	void SetRotation(glm::vec3 rotation) { Rotation = rotation; }
	void SetScale(glm::vec3 scale) { Scale = scale; }

	void Translate(glm::vec3 delta) { Position.x += delta.x; Position.y += delta.y; Position.z += delta.z; }
};

class ColorComponent : public Component {
public:

	glm::vec3 Color = { 1.0f,1.0f,1.0f };

	ColorComponent() = default;
	ColorComponent(const ColorComponent&) = default;
	ColorComponent(const glm::vec3& color) : Color(color) {}

};

class MaterialComponent : public Component {
public:

	Material material;

	MaterialComponent() = default;
	MaterialComponent(const MaterialComponent&) = default;
	MaterialComponent(const Material& material) : material(material) {}

};

class AnimationComponent : public Component {
public:

	AnimatedModel model;
	Animator animator;
	std::map<std::string, Animation*> animations;
	
	std::string selectedAnimation;


	AnimationComponent() = default;
	AnimationComponent(const AnimationComponent&) = default;
	AnimationComponent(AnimatedModel& model, Animator& animator) : model(model), animator(animator) {}

	void Update(float DeltaTime) {
		animator.UpdateAnimation(DeltaTime);
	}

	void AddAnimation(std::string name, std::string& path) {
		auto it = animations.begin();
		auto animation = new Animation(path, &model);
		animations.insert(it,std::pair<std::string,Animation*>(name, animation));
	}

	void SelectAnimation(std::string name) {
		selectedAnimation = name;
	}

	void Play() {
		if (!selectedAnimation.empty()) {
			if (animations.find(selectedAnimation) == animations.end()) {
				ENGINE_ERROR("The Animation component of this entity does not contain animation with name " + selectedAnimation);
			}
			else {
				animator.PlayAnimation(animations[selectedAnimation]);
			}
		}
	
	}

	void Render(Shader& animationShader) {
		animationShader.use();
		animationShader.setBool("animated", true);
		//animationShader.SetVec3("u_Color", { 1.0f,1.0f,1.0f }); // default white color
		model.Draw(animationShader);
	}
};


class MeshComponent : public Component {
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
	SphereCollider collider;
	float Radius;
	glm::vec3 Center;

	CircleColliderComponent() = default;
	CircleColliderComponent(const CircleColliderComponent&) = default;
	CircleColliderComponent(float radius, glm::vec3 center, glm::quat rotation) : Radius(radius), Center(center) {
		collider.SetCenter(center);
		collider.SetRadius(radius);
		collider.SetPosition(center);
		collider.SetRotation(rotation);
	}

};

class BoxColliderComponent : public Component {
public:
	BoxCollider collider;

	BoxColliderComponent() = default;
	BoxColliderComponent(const BoxColliderComponent&) = default;
	BoxColliderComponent(glm::vec3 size, glm::vec3 position, glm::quat rotation) {
		collider.SetSize(size);
		collider.SetPosition(position);
		collider.SetRotation(rotation);
		collider.SetCenter(position);
	}

};

class CapsuleColliderComponent : public Component {
public:
	CapsuleCollider collider;

	CapsuleColliderComponent() = default;
	CapsuleColliderComponent(const CapsuleColliderComponent&) = default;
	CapsuleColliderComponent(glm::vec3 position,glm::vec3 rotation,float height,float radius) {
		collider.SetRotation(rotation);
		collider.SetHeight(height);
		collider.SetRadius(radius);
		collider.SetPosition(position);
	}
	
};

class RigidBodyComponent : public Component {
public:
	RigidBody rigidbody;
	RigidBodyComponent() = default;
	RigidBodyComponent(const RigidBodyComponent&) = default;
	RigidBodyComponent(RigidBody& rb) : rigidbody(rb) {}

	void ApplyForce(glm::vec3 force) {
		rigidbody.ApplyForce(force);
	}

	void ApplyTorque(glm::vec3 torque) {
		rigidbody.ApplyTorque(torque);
	}

	void Translate(glm::vec3 velocity)
	{
		rigidbody.Translate(velocity);
	}

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

class TerrainComponent : public Component {
public:
	Terrain terrain;

	TerrainComponent() = default;
	TerrainComponent(const TerrainComponent&) = default;
	TerrainComponent(Terrain& t) : terrain(t) {}

	void SetGridSize(float gridSizeX, float gridSizeY)
	{
		terrain.SetGridSize(gridSizeX, gridSizeY);
	}
};

class PBRMaterialComponent : public Component
{
public:
	PBRMaterial material;

	PBRMaterialComponent() = default;
	PBRMaterialComponent(const PBRMaterialComponent&) = default;
	PBRMaterialComponent(PBRMaterial& material) : material(material) {}


};

class LightComponent : public Component {
public:
	Light light;

	LightComponent() = default;
	LightComponent(const LightComponent&) = default;
	LightComponent(Light& light) : light(light) {}
};

class ScriptComponent : public Component {
public:
	std::vector<LuaScript*> Scripts;

	ScriptComponent() = default;
	ScriptComponent(const ScriptComponent&) = default;

	bool AddScript(LuaScript* instance) {
		for (size_t i = 0; i < Scripts.size(); i++)
		{
			if (Scripts[i]->class_name == instance->class_name)
				return false;
		}
		Scripts.push_back(instance);
		return true;
	}

	bool RemoveScript(std::string instanceName) {
		for (size_t i = 0; i < Scripts.size(); i++) {
			if (Scripts[i]->class_name == instanceName) {
				if (Scripts[i]->hasDestroy) { Scripts[i]->CallMethod("Destroy"); }
				Scripts.erase(Scripts.begin() + i);
				return true;
			}
		}

		return false;
	}

	LuaScript* GetScript(std::string& scriptName)
	{
		for (size_t i = 0; i < Scripts.size(); i++)
		{
			if (Scripts[i]->class_name == scriptName)
				return Scripts[i];
		}
		return nullptr;
	}

	void Start() {
		for (size_t i = 0; i < Scripts.size(); i++) {
			if (Scripts[i]->hasStart)
				Scripts[i]->CallMethod("Start");
		}
	}
};