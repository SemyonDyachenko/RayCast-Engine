
#include "RigidBody.h"

namespace RayCast {

	RigidBody::RigidBody(Collider* collider, float mass, float linearDrag, float angularDrag, glm::vec3 linearVelocity, glm::vec3 angularVelocity)
		:
		m_iMass(1.0f / mass),
		m_LinearDrag(linearDrag),
		m_AngularDrag(angularDrag)
	{
		m_Mass = mass;
		m_AngularVelocity = angularVelocity;
		m_LinearVelocity = linearVelocity;

		m_isDynamic = true;

		m_Collider = collider;

		Position = m_Collider->Center;
		Rotation = m_Collider->Rotation;


		btDefaultMotionState* motionstate = new btDefaultMotionState(btTransform(
			btQuaternion(Rotation.x, Rotation.y, Rotation.z, Rotation.w), btVector3(Position.x, Position.y, Position.z)));

		btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(m_Mass, motionstate, collider->shape, btVector3(0.f, 0.f, 0.f));

		m_Body = new btRigidBody(rigidBodyCI);
	}

	void RigidBody::ApplyForce(glm::vec3 force)
	{
		if (m_Body)
			m_Body->applyCentralImpulse({ force.x,force.y,force.z });
	}

	void RigidBody::ApplyTorque(glm::vec3 torque)
	{
		if (m_Body)
			m_Body->applyTorque({ torque.x,torque.y,torque.z });
	}

	void RigidBody::ApplyImpulse(glm::vec3 impulse)
	{
		if (m_Body)
			m_Body->applyCentralImpulse({ impulse.x,impulse.y,impulse.z });
	}

	void RigidBody::ResetForce()
	{
		if (m_Body)
			m_Body->applyCentralImpulse({ 0.f,0.f,0.f });
	}

	void RigidBody::ResetTorque()
	{
		if (m_Body)
			m_Body->applyTorque({ 0.f,0.f,0.f });
	}



}