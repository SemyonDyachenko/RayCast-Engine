#pragma once


#include <GL/glew.h>
#define ENABLE_GLM_EXPERIMENTAL
#include <gtx/quaternion.hpp>

#include <glm.hpp>
#include "../Camera/Camera.h"
#include "../Rendering/Material.h"
#include "../Animation/AnimatedModel.h"
#include "../Animation/Animation.h"
#include "../Animation/Animator.h"
#include "../Light/LightPoint.h"
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
	};

	class ColorComponent : public Component {
	public:

		glm::vec3 Color = { 1.0f,1.0f,1.0f };

		ColorComponent() = default;
		ColorComponent(const ColorComponent&) = default;
		ColorComponent(const glm::vec3& color) : Color(color) {}

	};

	class CameraComponent : public Component {
	public:

		RayCast::Camera camera;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	class MaterialComponent : public Component {
	public:

		RayCast::Material material;

		MaterialComponent() = default;
		MaterialComponent(const MaterialComponent&) = default;
		MaterialComponent(const RayCast::Material& material) : material(material) {}

	};

	class AnimationComponent : public Component {
	public:

		RayCast::AnimatedModel model;
		RayCast::Animator animator;
		std::map<std::string, RayCast::Animation*> animations;

		AnimationComponent() = default;
		AnimationComponent(const AnimationComponent&) = default;
		AnimationComponent(RayCast::AnimatedModel& model, RayCast::Animator& animator) : model(model), animator(animator) {}

		void Update(float DeltaTime) {
			animator.UpdateAnimation(DeltaTime);
		}

		void AddAnimation(std::string name, RayCast::Animation* animation) {}
		void Play(std::string name) {
			animator.PlayAnimation(animations[name]);
		}

		void Render(RayCast::Shader& animationShader) {
			animationShader.use();
			animationShader.setBool("animated", true);
			animationShader.SetVec3("u_Color", { 1.0f,1.0f,1.0f }); // default white color
			model.Draw(animationShader);
		}
	};


	class MeshComponent : public Component {
	public:

		RayCast::Mesh mesh;
		glm::vec3 color;

		MeshComponent() = default;
		MeshComponent(const MeshComponent&) = default;
		MeshComponent(RayCast::Mesh& mesh, glm::vec3& color) : mesh(mesh), color(color) { this->mesh.SetSolidColor(this->color); }

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
		RayCast::SphereCollider collider;
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
		RayCast::BoxCollider collider;

		BoxColliderComponent() = default;
		BoxColliderComponent(const BoxColliderComponent&) = default;
		BoxColliderComponent(glm::vec3 size, glm::vec3 position, glm::quat rotation) {
			collider.SetSize(size);
			collider.SetPosition(position);
			collider.SetRotation(rotation);
			collider.SetCenter(position);
		}

	};

	class RigidBodyComponent : public Component {
	public:
		RayCast::RigidBody rigidbody;
		RigidBodyComponent() = default;
		RigidBodyComponent(const RigidBodyComponent&) = default;
		RigidBodyComponent(RayCast::RigidBody& rb) : rigidbody(rb) {}

	};

	class DirectionalLightComponent : public Component {
	public:
		RayCast::DirectionalLight light;
		DirectionalLightComponent() = default;
		DirectionalLightComponent(const DirectionalLightComponent&) = default;
		DirectionalLightComponent(RayCast::DirectionalLight& light) : light(light) {}
	};

	class LightPointComponent : public Component {
	public:
		RayCast::LightPoint light;
		glm::vec3 position;
		LightPointComponent() = default;
		LightPointComponent(const LightPointComponent&) = default;
		LightPointComponent(RayCast::LightPoint& light, glm::vec3 position) : light(light), position(position) { light.SetPosition(this->position); }
	};

	class TerrainComponent : public Component {
	public:
		RayCast::Terrain terrain;

		TerrainComponent() = default;
		TerrainComponent(const TerrainComponent&) = default;
		TerrainComponent(RayCast::Terrain& t) : terrain(t) {}

		void SetGridSize(float gridSizeX, float gridSizeY)
		{
			terrain.SetGridSize(gridSizeX, gridSizeY);
		}
	};

	class PBRMaterialComponent : public Component
	{
	public:
		RayCast::PBRMaterial material;

		PBRMaterialComponent() = default;
		PBRMaterialComponent(const PBRMaterialComponent&) = default;
		PBRMaterialComponent(RayCast::PBRMaterial& material) : material(material) {}


	};
