#pragma once

#include <glm.hpp>
#include "CollisionPoint.h"

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