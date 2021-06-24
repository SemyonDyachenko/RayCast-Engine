#pragma once

#include <glm.hpp>
#include "CollisionPoint.h"
#include <iostream>
#include <reactphysics3d/reactphysics3d.h>
#include "PhysicsEngine.h"
 

struct CollisionData {
public:

	CollisionData(bool hasCollision, float distance)
		: m_HasCollision(hasCollision),m_Distance(distance)
	{

	}

	inline bool IsCollision() const { return m_HasCollision; }
	inline float GetDistance() const { return m_Distance; }

private:
	const bool m_HasCollision;
	const bool m_Distance;
};

struct Collider {
public:
	//virtual CollisionData Intersect(const Collider& other) = 0;
	virtual ~Collider() = default;

};

struct BoxCollider : public Collider {
public:
	BoxCollider() {
	}
	BoxCollider(glm::vec3 size,glm::vec3 position,glm::quat rotation) : Size(size),Position(position),Rotation(rotation){
		
	}
	

	CollisionData Intersect(const BoxCollider& other) {
		bool collisionX = (Position.x + Size.x*2.f) >= other.Position.x && (other.Position.x + other.Size.x*2.f) >= Position.x;
		bool collisionY = Position.y + Size.y*2.f >= other.Position.y && other.Position.y + other.Size.y*2.f >= Position.y;
		bool collisionZ = (Position.z + Size.z*2.f) >= other.Position.z && other.Position.z + other.Size.z*2.f >= Position.z;

		std::cout << Size.x << " " << Size.y << " " << Size.z << "\n";

		return CollisionData(collisionX&&collisionY&&collisionZ, 0);
	}

public:
	glm::vec3 Size;
	glm::vec3 Position;
	glm::quat Rotation; 
};

struct CircleCollider : public Collider {
public:

	CircleCollider() {}
	CircleCollider(glm::vec3 center,float radius) : Center(center),Radius(radius)
	{
	}

	CollisionData Intersect(const CircleCollider& other) {
		float radiusDistance = Radius + other.Radius;
		glm::vec3 centerDistance = other.Center - Center;
		float centerDistanceLength = glm::length(centerDistance);

		float distance = centerDistanceLength - radiusDistance;

		return CollisionData(distance <= 0, distance);
	}

public:
	glm::vec3 Center;
	float Radius;
};



/*
struct Collider
{
	virtual CollisionPoints TestCollision(const Transform* transform, const Collider* collider, const Transform* colliderTransform) const = 0;
	virtual CollisionPoints TestCollision(const Transform* transform, const CircleCollider* collider, const Transform* circleTransform) const = 0;
	virtual CollisionPoints TestCollision(const Transform* transform, const BoxCollider* collider, const Transform* boxTransofrm) const  = 0;
};



struct CircleCollider : Collider
{
	glm::vec3 Center;
	float Radius;

	CollisionPoints TestCollision(const Transform* transform, const Collider* collider, const Transform* colliderTransform) const override {
		return collider->TestCollision(colliderTransform, this, transform);
	}
	CollisionPoints TestCollision(const Transform* transform, const CircleCollider* collider, const Transform* circleTransform) const override {
		return FindCircleCircleCollisionPoints(this, transform, collider, circleTransform);
	}

	CollisionPoints TestCollision(const Transform* transform, const BoxCollider* collider, const Transform* boxTransform) const override {
		return FindCircleBoxCollisionPoints(this, transform, collider, boxTransform);
	}

};


struct BoxCollider : Collider
{
	glm::vec3 Size;
	float Distance;

	CollisionPoints TestCollision(const Transform* transform, const Collider* collider, const Transform* colliderTransform) const override {
		return collider->TestCollision(colliderTransform, this, transform);
	}
	CollisionPoints TestCollision(const Transform* transform, const BoxCollider* collider, const Transform* boxTransform) const override {
		return FindBoxBoxCollisionPoints(this, transform, collider, boxTransform);
	}

	CollisionPoints TestCollision(const Transform* transform, const CircleCollider* collider, const Transform* circleTransform) const override {
		return FindBoxCircleCollisionPoints(this, transform, collider, circleTransform);
	}
};


CollisionPoints FindCircleCircleCollisionPoints(const CircleCollider* a, const Transform* ta, const CircleCollider* b, const Transform* tb) {}

CollisionPoints FindCircleBoxCollisionPoints(const CircleCollider* a, const Transform* ta, const BoxCollider* b, const Transform* tb) {}

CollisionPoints FindBoxCircleCollisionPoints(const BoxCollider* a, const Transform* ta, const CircleCollider* b, const Transform* tb) {}

CollisionPoints FindBoxBoxCollisionPoints(const BoxCollider* a, const Transform* ta, const BoxCollider* b, const Transform* tb) {}


#endif

*/