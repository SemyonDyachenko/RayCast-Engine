#ifndef DYNAMIC_WORLD_H
#define DYNAMIC_WORLD_H


#include "CollisionWorld.h"
#include "../Core/Log.h"
#include "PhysicsEngine.h"

class DynamicWorld 
{
public:

	void Init() {

	}

	void AddRigidBody(RigidBody* rigidbody) {
		rigidbody->SetGravity(m_Gravity);
		m_Objects.push_back(rigidbody);
		
	}

	void RemoveRigidBody(RigidBody* rigidbody) {
		if (!rigidbody) return;
		auto it = std::find(m_Objects.begin(), m_Objects.end(), rigidbody);	
		if (it == m_Objects.end()) return;
		m_Objects.erase(it);
	}

	void Update(float DeltaTime) {
		const reactphysics3d::decimal timeStep = 1.0f / 60.f;
		for (unsigned int i = 0; i < m_Objects.size(); i++)
		{
			for (unsigned int j = i + 1; j < m_Objects.size(); j++)
			{	

				CollisionData intersectData1 = m_Objects[i]->boxCollider->Intersect(*m_Objects[j]->boxCollider);

				if (intersectData1.IsCollision()) {
					m_Objects[i]->ApplyForce(glm::vec3(0.0f));
					m_Objects[i]->SetLinearVelocity(glm::vec3(0.0f));
					m_Objects[j]->ApplyForce(glm::vec3(0.0f));
					m_Objects[j]->SetLinearVelocity(glm::vec3(0.0f));

					ENGINE_INFO("COLLISION");
				}
			}
		}


		for (RigidBody* rb : m_Objects) {

			if (rb->IsDynamic()) {
				rb->ApplyForce(rb->GetGravity() * rb->GetMass());

				glm::vec3 velocity = rb->GetLinearVelocity() + (rb->GetForce() / rb->GetMass()) * DeltaTime;
				rb->SetLinearVelocity(velocity);
					
				glm::vec3 position = rb->GetPosition() + rb->GetLinearVelocity() * DeltaTime;

				rb->Position = position;

				rb->ResetForce();
			}
		}


		

	}

	unsigned int GetNumRigidBodies() { return (unsigned int)m_Objects.size(); }
	
private:
	glm::vec3 m_Gravity = { 0.f,-0.981, 0.f };

	std::vector<RigidBody*> m_Objects;


};



#endif