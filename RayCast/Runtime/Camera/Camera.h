#ifndef CAMERA_H
#define CAMERA_H


#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/string_cast.hpp> 
#include <gtx/quaternion.hpp>

#include "GLFW/glfw3.h"


enum class EditorCameraDirection {
	FORWARD = 0,
	BACK = 1,
	UP = 2,
	DOWN = 3,
	LEFT = 4,
	RIGHT = 5
};

enum class EditorCameraRotationDirection {
	LEFT = 0,
	RIGHT = 1,
	UP = 2,
	DOWN = 3
};


class AbstractCamera {
public:
	AbstractCamera() = default;

	virtual ~AbstractCamera() = default;
protected:
	glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
};

class Camera
{
public:
	Camera(glm::vec3 position, float aspectRatio, glm::vec3 up, glm::vec3 front, float fov, float nearplane, float farplane, glm::vec3 direction = glm::vec3(0.f));

	virtual ~Camera();

	void OnUpdate(float DeltaTime, GLFWwindow* window);

	void Move(EditorCameraDirection direction,float DeltaTime);
	void Rotate(EditorCameraRotationDirection direction, float DeltaTime);

	void Zoom(float ZoomFactor);

	void Recalculate();

	const glm::vec3& GetPosition();

	void CalculatePosition(float horizontalDistance, float verticalDistance);

	const glm::mat4& GetViewProjectionMatrix();
	const glm::mat4& GetViewMatrix() const;
	const glm::mat4& GetProjectionMatrix() const;

	const float& GetFov();

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
	glm::mat4 m_projectionMatrix;

};




#endif
