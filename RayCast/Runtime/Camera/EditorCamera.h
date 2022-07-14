#ifndef EDITOR_CAMERA
#define EDITOR_CAMERA

#include "Camera.h"

/*

class EditorCamera : public AbstractCamera
{
public:
	EditorCamera(float aspectRatio, float fov, float nearplane, float farplane);

	void OnUpdate(float DeltaTime, GLFWwindow* window);

	void Move(EditorCameraDirection direction, float DeltaTime);
	void Rotate(EditorCameraRotationDirection direction, float DeltaTime);

	void Zoom(float ScaleFactor);

	void Recalculate();

	const glm::vec3& GetPosition();

	void CalculatePosition(float horizontalDistance, float verticalDistance);

	const glm::mat4& GetViewProjectionMatrix();
	const glm::mat4& GetViewMatrix() const;
	const glm::mat4& GetProjectionMatrix() const;

	glm::quat GetOrientation() const;


private:
	glm::vec3 m_Position;
	glm::vec3 m_Direction;
	glm::vec3 m_Target;
	glm::vec3 m_Up;
	glm::vec3 m_cameraUp;
	glm::vec3 m_Right;
	glm::vec3 m_Front;

	float m_MovementSpeed;

	float m_yaw;
	float m_pitch;
	float m_roll;

	float m_aspectRatio;
	float m_fov;
	float m_nearPlane;
	float m_farPlane;

	glm::mat4 m_viewMatrix;

};


*/

#endif