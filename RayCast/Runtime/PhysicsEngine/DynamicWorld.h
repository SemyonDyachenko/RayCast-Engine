#ifndef DYNAMIC_WORLD_H
#define DYNAMIC_WORLD_H


#include "CollisionWorld.h"
#include "../Core/Log.h"
#include "PhysicsEngine.h"
#include "../../EntryPoint/Editor/GuiComponents/GuiConsole.h"
#include "../../Runtime/Utils/PlatformUtils.h"


class DynamicWorld 
{
public:

	DynamicWorld() {
		broadphase = new btDbvtBroadphase();
		collisionConfiguration = new btDefaultCollisionConfiguration();
		dispatcher = new btCollisionDispatcher(collisionConfiguration);
		solver =  new btSequentialImpulseConstraintSolver;
		dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
		dynamicsWorld->setGravity(btVector3(0, -9.81f, 0));
	}


	void SetGravity(glm::vec3 gravity) {
		dynamicsWorld->setGravity(PhysicUtils::GLMToBtVec3(gravity));
	}

	glm::vec3 GetGravity()  {
		glm::vec3 gravity = PhysicUtils::BtVec3ToGLM(dynamicsWorld->getGravity());
		return gravity;
	}

	void StepSimulation(float DeltaTime) {
		dynamicsWorld->stepSimulation(DeltaTime);
	}

	void UpdateCollision() {
		dynamicsWorld->updateAabbs();
	}

	void ClearBodies() {
		for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
		{
			btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
			btRigidBody* body = btRigidBody::upcast(obj);
			if (body && body->getMotionState())
			{
				delete body->getMotionState();
			}
			dynamicsWorld->removeCollisionObject(obj);
			delete obj;
		}
		m_Objects.clear();
	}

	void AddRigidBody(RigidBody* rigidbody) {

		if (rigidbody) {
			if (rigidbody->m_Collider != nullptr) {
				if (rigidbody->m_Body)
				{
					
					rigidbody->m_Body->setGravity(dynamicsWorld->getGravity());
					

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

	unsigned int GetNumRigidBodies() { return (unsigned int)m_Objects.size(); }
	
private:

	std::vector<RigidBody*> m_Objects;


	//Bullet Physics
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;
	

};



#endif