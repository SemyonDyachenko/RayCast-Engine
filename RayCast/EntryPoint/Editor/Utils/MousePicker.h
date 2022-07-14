#pragma once

#include <glm.hpp>
#include "../../../Runtime/Camera/Camera.h"

class MousePicker {
private:
	glm::vec3 _currentRay;
	glm::mat4 _projectionMatrix;
	glm::mat4 _viewMatrix;

	EditorCamera* m_Camera;

public:
	MousePicker(EditorCamera& camera, glm::mat4 projection) {
		_projectionMatrix = projection;
		_viewMatrix = camera.GetViewMatrix();
		m_Camera = &camera;
		
	}

	glm::vec3& GetCurrentRay() {
		return _currentRay;
	}

	void Update() {
		_viewMatrix = m_Camera->GetViewMatrix();
		_currentRay = calculateMouseRay();
	}

private:
	glm::vec3 calculateMouseRay() {
		double mouseX, mouseY;
		glfwGetCursorPos((GLFWwindow*)Game::GetWindow().GetNativeWindow(), &mouseX, &mouseY);
		glm::vec2 normalizedCoords = GetNormalizedDeviceCoords(mouseX, mouseY);
		glm::vec4 clipCoords = glm::vec4(normalizedCoords.x, normalizedCoords.y, -1.f, 1.f);
		glm::vec4 eyeCoords = ToEyeCoords(clipCoords);
		glm::vec3 worldRay = ToWorldCoords(eyeCoords);
		return worldRay;
	}

	glm::vec3 ToWorldCoords(glm::vec4 EyeCoords) {
		glm::mat4 invertedView = glm::inverse(_viewMatrix);
		glm::vec4 rayWorld = invertedView * EyeCoords;
		glm::vec3 mouseRay = glm::vec3(rayWorld.x, rayWorld.y, rayWorld.z);
		glm::vec3 normalizedRay = glm::normalize(mouseRay);
		return normalizedRay;
	}

	glm::vec4 ToEyeCoords(glm::vec4 clipCoords) {
		glm::mat4 invertedProjection = glm::inverse(_projectionMatrix);
		glm::vec4 eyeCoords = invertedProjection * clipCoords;
		return glm::vec4(eyeCoords.x, eyeCoords.y, -1.f, 0);
	}


	glm::vec2 GetNormalizedDeviceCoords(double mouseX, double mouseY) {
		float x = (2.f * mouseX) / Game::GetWindow().GetWidth() - 1;
		float y = (2.f * mouseY) / Game::GetWindow().GetHeight() - 1.f;
		return glm::vec2(x, y);
	}




};