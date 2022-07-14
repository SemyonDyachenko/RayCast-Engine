#include "../../stdafx.h"
#include "RigidBody.h"



RigidBody::RigidBody(Collider* collider, float mass, float linearDrag, float angularDrag, glm::vec3 linearVelocity, glm::vec3 angularVelocity)
	:
	m_iMass(1.0f / mass),
	m_LinearDrag(linearDrag),
	m_AngularDrag(angularDrag)
{
	m_Mass = mass;
	m_AngularVelocity = angularVelocity;
	m_LinearVelocity = linearVelocity;

	m_Collider = collider;
	
	btDefaultMotionState* motionstate = new btDefaultMotionState(btTransform(PhysicUtils::GLMQuatToBt(collider->Rotation),PhysicUtils::GLMToBtVec3(m_Collider->Center)));

	btVector3 localInertia(0, 0, 0);
	collider->shape->calculateLocalInertia(m_Mass, localInertia);

	m_Body = new btRigidBody(btRigidBody::btRigidBodyConstructionInfo(m_Mass, motionstate, collider->shape));
	
	if (collider->HasPhysicMaterial) {
		m_Body->setFriction(collider->material.m_Friction);
		m_Body->setRollingFriction(collider->material.m_Friction);	
		m_Body->setRestitution(collider->material.m_Bounciness);
	}

	//m_Body->setDamping(m_LinearDrag, m_AngularDrag);

	//m_Body->intertia


}

void RigidBody::Translate(glm::vec3 velocity)
{
	m_Body->activate(true);
	if (m_Body)
		m_Body->translate({ velocity.x, velocity.y, velocity.z});
}



void RigidBody::ApplyForce(glm::vec3 force)
{
	m_Body->activate(true);
	m_Body->setLinearVelocity(m_Body->getLinearVelocity() + btVector3(force.x, force.y, force.z));
}

void RigidBody::ApplyTorque(glm::vec3 torque)
{
	m_Body->activate(true);
	if (m_Body)
		m_Body->applyTorque({ torque.x,torque.y,torque.z });
}


void RigidBody::ResetForce()
{
	m_Body->activate(true);
	if (m_Body)
		m_Body->applyCentralForce({ 0.f,0.f,0.f });
}

void RigidBody::ResetTorque()
{
	m_Body->activate(true);
	if (m_Body)
		m_Body->applyTorque({ 0.f,0.f,0.f });
}

void RigidBody::ResetVelocity()
{
	m_Body->setLinearVelocity({ 0.0f,0.0f,0.0f });
	m_Body->setAngularVelocity({ 0.0f,0.0f,0.0f });
}


