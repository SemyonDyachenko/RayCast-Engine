#pragma once

#include "../../Runtime/Entity/ScriptableEntity.h"
#include "../../Runtime/Core/Input.h"

/*
class MovementController : public ScriptableEntity
{
public:
	void OnCreate() override {

	}

	void OnUpdate(float DeltaTime) override {
		TransformComponent& ts = GetComponent<TransformComponent>();

		if (Input::IsKeyPressed(INPUT_KEY_T)) {
			ts.Position.y += 0.3f * DeltaTime;
		}
	}

	void OnDestroy() override {

	}
};

*/