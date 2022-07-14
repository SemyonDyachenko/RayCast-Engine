#pragma once


#include "../Camera/Camera.h"
#include "Component.h"


class CameraComponent : public Component {
public:

	Camera* camera;
	bool Primary;

	CameraComponent(const CameraComponent&) = default;
	CameraComponent() {
		camera = new Camera();
		Primary = false;
	}

	Entity * GetTarget() const
	{
		return camera->GetTarget();
	}

	glm::vec3 GetForward()
	{
		return camera->GetForwardDirection();
	}

	void SetPosition(glm::vec3 position)
	{
		camera->SetPosition(position);
	}
};
