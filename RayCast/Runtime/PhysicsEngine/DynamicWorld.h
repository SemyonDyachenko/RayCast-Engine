#ifndef DYNAMIC_WORLD_H
#define DYNAMIC_WORLD_H


#include "CollisionWorld.h"

/*
class DynamicWorld : CollisionWorld
{
public:
	void AddRigidBody(RigidBody* rigidbody) {
		rigidbody->SetGravity(m_Gravity);

		AddCollisionObject(rigidbody);
	}

	void Update(float DeltaTime) {
		for (CollisionObject* object : m_Objects) {
			if(!object->IsDynamic()) continue;
			RigidBody* rigidbody = (RigidBody*)object;

			rigidbody->ApplyForce(rigidbody->GetGravity() * rigidbody->GetMass());

			glm::vec3 velocity = rigidbody->GetLinearVelocity() + rigidbody->GetForce() / rigidbody->GetMass();

			glm::vec3 position = rigidbody->GetPosition() + rigidbody->GetLinearVelocity() * DeltaTime;

			rigidbody->SetLinearVelocity(velocity);
			rigidbody->SetPosition(position);

			rigidbody->ResetForce();
;		}
	}
private:
	glm::vec3 m_Gravity = { 0,-9.81f, 0 };
};

*/

#endif