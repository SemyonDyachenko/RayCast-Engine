#include "RigidBody.h"

RigidBody::RigidBody(float mass, float linearDrag, float angularDrag, glm::vec3 linearVelocity, glm::vec3 angularVelocity)
	: 
	m_iMass(1.0f / mass),
	m_LinearDrag(linearDrag),
	m_AngularDrag(angularDrag)
{
	m_Mass = mass;
	m_AngularVelocity = angularVelocity;
	m_LinearVelocity = linearVelocity;

	m_isDynamic = true;
}

void RigidBody::ApplyForce(glm::vec3 force)
{
	m_Force += force;
}

void RigidBody::ApplyTorque(glm::vec3 torque)
{
	m_Torque += torque;
}

void RigidBody::ApplyImpulse(glm::vec3 impulse)
{
}

void RigidBody::ResetForce()
{
	m_Force = glm::vec3(0.f, 0.f, 0.f);
}

void RigidBody::ResetTorque()
{
	m_Torque = glm::vec3(0.f, 0.f, 0.f);
}


