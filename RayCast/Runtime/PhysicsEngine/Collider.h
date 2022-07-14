#pragma once

#include <glm.hpp> 
#include "CollisionPoint.h"
#include <iostream>
#include "PhysicsEngine.h"

#include "PhysicsMaterial.h"
#include "../Rendering/Mesh.h"


class Collider {

public:
	~Collider() = default;


	glm::vec3 Center;
	glm::quat Rotation;
	glm::vec3 Position;
	btCollisionShape* shape;
	PhysicsMaterial material;

	bool HasPhysicMaterial = false;
};

class SphereCollider  : public Collider {
public:
	SphereCollider() {
		Radius = 1.0f;
		Center = glm::vec3(1.0f);
		CreateShape();
	}
	SphereCollider(float radius,glm::vec3 center) : Radius(radius) {
		Center = center;
		CreateShape();
	}

	void SetRadius(float radius) { Radius = radius; shape = new btSphereShape(Radius);  }
	void SetCenter(glm::vec3 center) { Center = center; }
	void SetRotation(glm::quat rotation) { Rotation = rotation; }
	void SetPosition(glm::vec3 position) { Position = position; }

	float GetRadius() { return Radius; }
	
public:
	float Radius;
	void CreateShape() {
		shape = new btSphereShape(Radius);
	}
};

class BoxCollider : public Collider {
public:
	BoxCollider() {
		Size = glm::vec3(1.0f);
		Center = glm::vec3(1.0f);
		CreateShape();
	}
	BoxCollider(glm::vec3 size,glm::vec3 center) : Size(size) {
		Center = center;
		CreateShape();
	}

	void SetSize(glm::vec3 size) { Size = size; shape = new btBoxShape({ Size.x,Size.y,Size.z }); }
	void SetRotation(glm::quat rotation) { Rotation = rotation; }
	void SetPosition(glm::vec3 position) { Position = position; }
	void SetCenter(glm::vec3 center) { Center = center; }

	glm::vec3& GetSize() { return Size; }

public:
	glm::vec3 Size;
	void CreateShape() {
		shape = new btBoxShape({Size.x,Size.y,Size.z});
	}
};

class CapsuleCollider : public Collider {
public:
	CapsuleCollider() {
		Radius = 1.0f;
		Height = 2.f;
		CreateShape();
	}

	CapsuleCollider(float radius, float height)
	: Radius(radius),Height(height) {
		CreateShape();
	}

	void SetRotation(glm::quat rotation) { Rotation = rotation; }
	void SetPosition(glm::vec3 position) { Position = position; }

	void SetHeight(float height) { Height = height; CreateShape(); }
	void SetRadius(float radius) { Radius = radius; CreateShape(); }

	float& GetRadius() { return Radius; }
	float& GetHeight() { return Height; }
public:
	float Radius;
	float Height;

	void CreateShape() {
		shape = new btCapsuleShape(Radius, Height);
	}
};

