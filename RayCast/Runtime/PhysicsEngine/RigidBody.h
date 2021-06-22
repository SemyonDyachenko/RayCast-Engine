#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <glm.hpp>
#include "Collider.h"
#include <gtx/quaternion.hpp>
#include <functional>
#include "CollisionPoint.h"
#include "BoxCollider.h"

enum class RigidBodyType {
	STATIC = 0,
	DYNAMIC
};


struct CollisionObject {
public:
	bool& IsDynamic() { return m_isDynamic; }

protected:
	BoxCollider* collider;
	glm::vec3 Position;
	glm::quat Rotation;


	bool m_isDynamic;
	bool isTrigger;
};



struct RigidBody :  CollisionObject
{
public:
	RigidBody() {}

	RigidBody(float mass = 1.0f, float linearDrag = 1.0f, float angularDrag = 1.0f, glm::vec3 velocity = glm::vec3(0.0f), glm::vec3 angularVelocity = glm::vec3(0.0f));

	virtual ~RigidBody() = default;

	void ApplyForce(glm::vec3 force);
	void ApplyTorque(glm::vec3 torque);
	void ApplyImpulse(glm::vec3 impulse);

	void ResetForce();
	void ResetTorque();


	glm::vec3& GetForce() { return m_Force; }
	glm::vec3& GetTorque() { return m_Torque; };

	float& GetMass() { return m_Mass; }
	float& GetLinearDrag() { return m_LinearDrag; }
	float& GetAngularDrag() { return m_AngularDrag; }

	float& GetStaticFriction() { return m_StaticFriction; }
	float& GetDynamicFriction() { return m_DynamicFriction; }

	glm::vec3& GetGravity() { return m_Gravity; }
	glm::vec3& GetLinearVelocity() { return m_LinearVelocity; }
	glm::vec3& GetAngularVelocity() { return m_AngularVelocity; }

	glm::vec3& GetPosition() { return Position; }
	glm::quat& GetRotation() { return Rotation; }

	void SetLinearVelocity(glm::vec3 velocity) { m_LinearVelocity = velocity; }
	void SetPosition(glm::vec3 position) { Position = position; }

	void SetGravity(glm::vec3 gravity) { m_Gravity = gravity; }
	void SetMass(float mass) { m_Mass = mass; }
	void SetLinearDrag(float linearDrag) { m_LinearDrag = linearDrag; }
	void SetAngularDrags(float angularDrag) { m_AngularDrag = angularDrag; }

	

private:
	glm::vec3 m_Gravity;
	float m_iMass;
	float m_LinearDrag;
	float m_AngularDrag;

	glm::vec3 m_AngularVelocity;
	glm::vec3 m_LinearVelocity;
	glm::vec3 m_Force;
	glm::vec3 m_Torque;
	float m_Mass;

	float m_StaticFriction;
	float m_DynamicFriction;


};


#endif