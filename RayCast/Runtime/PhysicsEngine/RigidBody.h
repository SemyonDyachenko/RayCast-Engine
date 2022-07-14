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

constexpr glm::vec3 NULL_GRAVITY = glm::vec3(0, 0, 0);
constexpr glm::vec3 DEFAULT_GRAVITY = glm::vec3(0, -9.81f, 0);


class RigidBody 
{
public:
	
	RigidBody(Collider* collider, float mass = 1.0f, float linearDrag = 1.0f, float angularDrag = 1.0f, glm::vec3 linearVelocity = glm::vec3(0.0f), glm::vec3 angularVelocity = glm::vec3(0.0f));

	virtual ~RigidBody() = default;

	void Translate(glm::vec3 velocity);
	
	void ApplyForce(glm::vec3 force);
	void ApplyTorque(glm::vec3 torque);

	void ResetForce();
	void ResetTorque();

	void ResetVelocity();

	bool& TakesGravity() {
		if (m_TakesGravity)
			m_Body->setGravity(PhysicUtils::GLMToBtVec3(DEFAULT_GRAVITY));
		else
			m_Body->setGravity(PhysicUtils::GLMToBtVec3(NULL_GRAVITY));

		return m_TakesGravity;
	}
	
	bool& IsKinematic() {
		return m_Kinematic;
	}

	void UpdateKinematic() {
		if(m_Kinematic)
			m_Body->setCollisionFlags(m_Body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
	}

	float& GetMass() { return m_Mass; }
	float& GetLinearDrag() { return m_LinearDrag; }
	float& GetAngularDrag() { return m_AngularDrag; }

	void SetLinearVelocity(glm::vec3 velocity) { m_LinearVelocity = velocity; m_Body->setLinearVelocity({ m_LinearVelocity.x,m_LinearVelocity.y,m_LinearVelocity.z }); }

	void Teleport(glm::vec3 position, glm::quat rotation) {
		btTransform transform;
		transform.setIdentity(); 
		
		const btVector3 pos = btVector3(position.x, position.y, position.z);
		const btQuaternion rotaiton = btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w);

		transform.setOrigin(pos);
		transform.setRotation(rotaiton);

		m_Body->setWorldTransform(transform);
	}


	void SetGravity(glm::vec3 gravity) { m_Gravity = gravity; m_Body->setGravity(PhysicUtils::GLMToBtVec3(m_Gravity)); }

	void SetMass(float mass) { 
		m_Mass = mass; 
		m_Body->setMassProps(m_Mass, { 0.f,0.f,0.f });
		m_Body->updateInertiaTensor();
	}
	void SetLinearDrag(float linearDrag) { m_LinearDrag = linearDrag; }
	void SetAngularDrag(float angularDrag) { m_AngularDrag = angularDrag; }

	void ApplyPhysicMaterial() {
		if (m_Collider->HasPhysicMaterial) {
			m_Body->setFriction(m_Collider->material.m_Friction);
			m_Body->setRestitution(m_Collider->material.m_Bounciness);
		}
	}
	btTransform& GetWorldTransform() {
		return m_Body->getWorldTransform();
	}

public:
	Collider* m_Collider = nullptr;
	btRigidBody* m_Body = nullptr;

private:

	btVector3 inertia = { 0.0f, 0.0f, 0.0f };

	glm::vec3 m_Gravity;
	float m_iMass;
	float m_LinearDrag = 0.01f;
	float m_AngularDrag = 0.f;

	glm::vec3 m_AngularVelocity;
	glm::vec3 m_LinearVelocity;
	glm::vec3 m_Force;
	glm::vec3 m_Torque;
	float m_Mass;

	float m_StaticFriction;
	float m_DynamicFriction;

	bool m_TakesGravity = true;
	bool m_Kinematic = false;


	friend class Collider;


};


#endif