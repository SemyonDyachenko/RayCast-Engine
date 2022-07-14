#ifndef SCRIPT_ENGINE_H
#define SCRIPT_ENGINE_H


#include "ScriptManager.h"
#include "LuaBridge/LuaBridge.h"
#include "../Entity/Component.h"
#include "../Entity/CameraComponent.h"
#include "../Core/Input.h"

#include <gtc/matrix_transform.hpp>
#include <gtx/euler_angles.hpp>

#include "../Math/LuaMath.h"

struct Vec3Helper
{
	template<unsigned index>
	static float get(glm::vec3 const* vec)
	{
		if (index == 0)
			return vec->x;
		if (index == 1)
			return vec->y;

		return vec->z;
	}

	template<unsigned index>
	static void set(glm::vec3* vec, float value)
	{
		if (index == 0) {
			vec->x = value;
			return;
		}
		if (index == 1) {
			vec->y = value;
			return;
		}

		vec->z = value;
	}

	// Operators
	// -----------------------------------------
	static glm::vec3* ADD(glm::vec3* vec, glm::vec3* vecTow)
	{
		vec->x += vecTow->x;
		vec->y += vecTow->y;
		vec->z += vecTow->z;
		return vec;
	}
	static glm::vec3* MUL(glm::vec3* vec, glm::vec3* vecTow)
	{
		vec->x *= vecTow->x;
		vec->y *= vecTow->y;
		vec->z *= vecTow->z;
		return vec;
	}
	static glm::vec3* DIV(glm::vec3* vec, glm::vec3* vecTow)
	{
		vec->x /= vecTow->x;
		vec->y /= vecTow->y;
		vec->z /= vecTow->z;
		return vec;
	}
	static glm::vec3* SUB(glm::vec3* vec, glm::vec3* vecTow)
	{
		vec->x -= vecTow->x;
		vec->y -= vecTow->y;
		vec->z -= vecTow->z;
		return vec;
	}

	static bool lessThen(glm::vec3* a, glm::vec3* b)
	{
		return (a < b);
	}

	static bool LessOrEq(glm::vec3* a, glm::vec3* b)
	{
		return (a <= b);
	}

	static bool Equale(glm::vec3* a, glm::vec3* b)
	{
		return (a == b);
	}

	static glm::vec3 VecUp()
	{
		return glm::vec3(0.0f, 1.0f, 0.0f);
	}

	static glm::vec3 VecRight()
	{
		return glm::vec3(1.0f, 0.0f, 0.0f);
	}

	static glm::vec3 VecForward()
	{
		return glm::vec3(0.0f, 0.0f, 1.0f);
	}

	static glm::vec3 Vec3F(float val)
	{
		return glm::vec3(val, val, val);
	}

	static glm::vec3 Lerp(glm::vec3 a, glm::vec3 b, float d)
	{
		return glm::lerp(a, b, d);
	}

	static std::string __gettype(glm::vec3* vec)
	{
		return "VEC3";
	}

	static glm::vec3 Distance(glm::vec3 a,glm::vec3 b)
	{
		return (a - b);
	}

};


struct Vec2Helper
{
	template<unsigned index>
	static float get(glm::vec2 const* vec)
	{
		if (index == 0)
			return vec->x;
		if (index == 1)
			return vec->y;
	}

	template<unsigned index>
	static void set(glm::vec2* vec, float value)
	{
		if (index == 0) {
			vec->x = value;
			return;
		}
		if (index == 1) {
			vec->y = value;
			return;
		}
	}

	// Operators
	// -----------------------------------------
	static glm::vec2* ADD(glm::vec2* vec, glm::vec2* vecTow)
	{
		vec->x += vecTow->x;
		vec->y += vecTow->y;
		return vec;
	}
	static glm::vec2* MUL(glm::vec2* vec, glm::vec2* vecTow)
	{
		vec->x *= vecTow->x;
		vec->y *= vecTow->y;
		return vec;
	}
	static glm::vec2* DIV(glm::vec2* vec, glm::vec2* vecTow)
	{
		vec->x /= vecTow->x;
		vec->y /= vecTow->y;
		return vec;
	}
	static glm::vec2* SUB(glm::vec2* vec, glm::vec2* vecTow)
	{
		vec->x -= vecTow->x;
		vec->y -= vecTow->y;
		return vec;
	}

	static bool lessThen(glm::vec2* a, glm::vec2* b)
	{
		return (a < b);
	}

	static bool LessOrEq(glm::vec2* a, glm::vec2* b)
	{
		return (a <= b);
	}

	static bool Equale(glm::vec2* a, glm::vec2* b)
	{
		return (a == b);
	}


	static glm::vec2 Vec2F(float val)
	{
		return glm::vec2(val, val);
	}

	static std::string __gettype(glm::vec2* vec)
	{
		return "VEC@";
	}

};



class ScriptEngine {
public:
	ScriptEngine() {}
	~ScriptEngine() {}

	static void InitLua(lua_State* state) {
		luabridge::getGlobalNamespace(state)
			.beginClass<glm::vec3>("Vector3")
			.addConstructor<void(*) (float, float, float)>()
			.addProperty("x", &Vec3Helper::get<0>, &Vec3Helper::set<0>)
			.addProperty("y", &Vec3Helper::get<1>, &Vec3Helper::set<1>)
			.addProperty("z", &Vec3Helper::get<2>, &Vec3Helper::set<2>)
			.addStaticFunction("Distance", &Vec3Helper::Distance)
			.addStaticFunction("Lerp", &Vec3Helper::Lerp)
			.addStaticFunction("SUB", &Vec3Helper::SUB)
			.endClass()
			.beginClass<glm::vec2>("Vector2")
			.addConstructor<void(*) (float, float)>()
			.addProperty("x", &Vec2Helper::get<0>, &Vec2Helper::set<0>)
			.addProperty("y", &Vec2Helper::get<1>, &Vec2Helper::set<1>)
			.endClass()
			.beginClass<TransformComponent>("Transform")
			.addConstructor<void(*) ()>()
			.addFunction("Translate", &TransformComponent::Translate)
			.addFunction("SetPosition", &TransformComponent::SetPosition)
			.addFunction("SetRotation", &TransformComponent::SetRotation)
			.addFunction("SetScale", &TransformComponent::SetScale)
			.addFunction("GetPosition", &TransformComponent::GetPosition)
			.addFunction("GetRotation", &TransformComponent::GetRotation)
			.addFunction("GetScale", &TransformComponent::GetScale)
			.endClass()
			.beginClass<RigidBodyComponent>("RigidBody")
			.addFunction("ApplyForce", &RigidBodyComponent::ApplyForce)
			.addFunction("ApplyTorque", &RigidBodyComponent::ApplyTorque)
			.addFunction("Translate",&RigidBodyComponent::Translate)
			.endClass()
			.beginClass<AnimationComponent>("Animator")
			.addFunction("Play", &AnimationComponent::Play)
			.endClass()
			.beginClass<Entity>("Entity")
			.addConstructor<void(*) ()>()
			.addFunction("GetID", &Entity::GetId)
			.addFunction("GetName", &Entity::GetName)
			.addFunction("GetTransform", &Entity::GetComponent<TransformComponent>)
			.addFunction("AddTransform", &Entity::AddComponent<TransformComponent>)
			.addFunction("GetRigidBody", &Entity::GetComponent<RigidBodyComponent>)
			.addFunction("GetAnimator", &Entity::GetComponent<AnimationComponent>)
			.addFunction("GetCamera", &Entity::GetComponent<CameraComponent>)
			.endClass()
			.beginClass<LuaInput>("Input")
			.addConstructor<void(*) ()>()
			.addFunction("GetKey", &LuaInput::StringToKey)
			.addFunction("IsKeyPressed", &LuaInput::IsKeyPressed)
			.addFunction("IsMouseButtonPressed", &LuaInput::IsMouseButtonPressed)
			.addFunction("IsKeyReleased", &LuaInput::IsKeyReleased)
			.addFunction("GetMousePosition", &LuaInput::GetMousePosition)
			.addFunction("SetMousePosition", &LuaInput::SetMousePosition)
			.addFunction("GetMouseDelta",&LuaInput::GetMouseDelta)
			.endClass()
			.beginClass<EntityManager>("EntityManager")
			.addConstructor<void(*) ()>()
			.addFunction("GetEntity", &EntityManager::GetEntityById)
			.endClass()
			.beginClass<CameraComponent>("Camera")
			.addFunction("GetTarget", &CameraComponent::GetTarget)
			.addFunction("GetForward",&CameraComponent::GetForward)
			.addFunction("SetPosition",&CameraComponent::SetPosition)
			.endClass()
			.beginClass<LuaMath>("Math")
			.addConstructor<void(*) ()>()
			.addStaticFunction("Sin",&LuaMath::Sin)
			.addStaticFunction("Cos",&LuaMath::Cos)
			.addStaticFunction("Tan",&LuaMath::Tan)
			.addStaticFunction("PI",&LuaMath::PI)
			.addStaticFunction("Radians",&LuaMath::Radians)
			.endClass();
	}

};

#endif 