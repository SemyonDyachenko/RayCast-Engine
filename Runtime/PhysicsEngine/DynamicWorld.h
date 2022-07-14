#ifndef DYNAMIC_WORLD_H
#define DYNAMIC_WORLD_H


#include "CollisionWorld.h"
#include "../Core/Log.h"
#include "PhysicsEngine.h"
#include "../../Runtime/Utils/PlatformUtils.h"

namespace RayCast {

	class RAYCAST_API DynamicWorld
	{
	public:

		DynamicWorld() {
			broadphase = new btDbvtBroadphase();
			collisionConfiguration = new btDefaultCollisionConfiguration();
			dispatcher = new btCollisionDispatcher(collisionConfiguration);
			solver = new btSequentialImpulseConstraintSolver;
			dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
			dynamicsWorld->setGravity(btVector3(0, -9.81f, 0));
		}

		void AddRigidBody(RigidBody* rigidbody) {

			if (rigidbody) {
				if (rigidbody->m_Collider != nullptr) {
					if (rigidbody->m_Body)
					{
						rigidbody->SetGravity(m_Gravity);
						m_Objects.push_back(rigidbody);


						dynamicsWorld->addRigidBody(rigidbody->m_Body);
					}
					else
					{
						ENGINE_ERROR("Entity has not a Rigid Body!");
					}
				}
				else {
					ENGINE_ERROR("impossible to create a rigid body, there is no collider");
				}
			}
		}

		void RemoveRigidBody(RigidBody* rigidbody) {
			if (!rigidbody) return;
			auto it = std::find(m_Objects.begin(), m_Objects.end(), rigidbody);
			if (it == m_Objects.end()) return;
			m_Objects.erase(it);
			dynamicsWorld->removeRigidBody(rigidbody->m_Body);
		}

		void Update(float DeltaTime) {

			dynamicsWorld->stepSimulation(DeltaTime);

			std::cout << dynamicsWorld->getNumCollisionObjects() << "\n";
			for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
			{
				btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
				btRigidBody* body = btRigidBody::upcast(obj);
				btTransform trans;
				if (body && body->getMotionState())
				{
					body->getMotionState()->getWorldTransform(trans);
				}
				else
				{
					trans = obj->getWorldTransform();
				}
			}

		}

		unsigned int GetNumRigidBodies() { return (unsigned int)m_Objects.size(); }

	private:
		glm::vec3 m_Gravity = { 0.f,-0.981, 0.f };

		std::vector<RigidBody*> m_Objects;


		//Bullet Physics
		btBroadphaseInterface* broadphase;
		btDefaultCollisionConfiguration* collisionConfiguration;
		btCollisionDispatcher* dispatcher;
		btSequentialImpulseConstraintSolver* solver;
		btDiscreteDynamicsWorld* dynamicsWorld;


	};

}


#endif