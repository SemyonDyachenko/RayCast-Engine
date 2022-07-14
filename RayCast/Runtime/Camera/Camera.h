#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/string_cast.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/quaternion.hpp>

#include "../Core/Game.h"

#include "../Entity/Entity.h"

/* CAMERA CLASS, No Editor Camera, use in Runtime */

/* CAMERA COMPONENT */
class Camera {
public:
	
	Camera() {
		Init();
	}
	
	// Initialize default camera variables
	void Init() {
		m_Fov = 60.f;
		m_AspectRatio = static_cast<float>(Game::GetWindow().GetWidth()) / static_cast<float>(Game::GetWindow().GetHeight());
		m_Position = { 0,0,0 };
		m_Yaw = 0.f;
		m_Roll = 0.0f;
		m_Pitch = 0.0f;
		m_OnUpdate = false;

		
		// maybe const
		glm::quat orientation = GetOrientation();
		m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), m_AspectRatio, m_NearPlane, m_FarPlane);
		//m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(orientation);
		//m_ViewMatrix = glm::inverse(m_ViewMatrix);

		glm::vec3 targetPosition = m_TargetPosition;
		
		if (m_Target)
			targetPosition = m_Target->GetComponent<TransformComponent>().Position;

		m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(GetOrientation());
		m_ViewMatrix = glm::inverse(m_ViewMatrix);
	}

	virtual ~Camera() = default;

	virtual glm::vec3& GetPosition() {
		return m_Position;
	}

	virtual void SetAspectRatio(float width,float height)
	{
		m_AspectRatio = width / height;
		RecalculateMatrices();
	}
	
	virtual void SetPosition(glm::vec3 position) {
		RecalculateMatrices();
		m_Position = position;
		RecalculateMatrices();
	}


	virtual void SetRotation(float yaw,float pitch)
	{
		RecalculateMatrices();
		m_Yaw = yaw;
		m_Pitch = pitch;
		RecalculateMatrices();
	}
	
	// choose transform data to set a target
	virtual void LookAt(Entity *entity)
	{
		m_Target = entity;
	}

	virtual void LookAt(glm::vec3 position)
	{
		if (!HasTarget())
			m_TargetPosition = position;

	}

	virtual void SetYaw(float yaw)
	{
		m_Yaw = yaw;
		RecalculateMatrices();
	}

	virtual bool HasTarget()
	{
		return m_Target != nullptr;
	}

	virtual Entity * GetTarget() const
	{
		return m_Target;
	}


	virtual void SetPitch(float pitch)
	{
		m_Pitch = pitch;
		RecalculateMatrices();
	}

	const glm::mat4& GetProjectionMatrix() const
	{
		return m_ProjectionMatrix;
	}

	const glm::mat4& GetViewMatrix() const
	{
		return m_ViewMatrix;
	}


	// editor viewport
	virtual void OnResize(float width,float height) {
		m_AspectRatio = width / height;
		RecalculateMatrices();
	}

	virtual float& GetYaw() {
		return m_Yaw;
	}
	virtual float& GetRoll() {
		return m_Roll;
	}
	virtual float& GetPitch() {
		return m_Pitch;
	}

	// use or unuse camera
	void Update(bool state) { m_OnUpdate = state; }


	// checks if the camera is used as the main one at the moment
	const bool& OnUpdate() const { return m_OnUpdate; }

	// recalculate view matrix
	void UpdateView() {
		m_ViewMatrix = glm::translate(glm::mat4(1.0f),m_Position) * glm::toMat4(GetOrientation());
		m_ViewMatrix = glm::inverse(m_ViewMatrix);
	}
	
	// recalculate projection matrix
	void UpdateProjection() {
		m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), m_AspectRatio, m_NearPlane, m_FarPlane);
	}

	virtual void SetFov(float fov)
	{
		m_Fov = fov;
		RecalculateMatrices();
	}

	// Rotate camera (change yaw and pitch) use mouse position delta
	virtual void Rotate(glm::vec2& delta,float speed)
	{
		m_Yaw += delta.x * speed;
		m_Pitch += delta.y * speed;
	}

	glm::vec3 GetRightDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	glm::vec3 GetForwardDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
	}

	glm::vec3 GetUpDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	// Get rotation in quaternion
	glm::quat GetOrientation() const
	{
		return glm::quat(glm::vec3(-m_Pitch, -m_Yaw, 0.0f));
	}

	virtual float& GetFov()
	{
		return m_Fov;
	}

	virtual float & GetNearPlane()
	{
		return m_NearPlane;
	}

	virtual float& GetFarPlane()
	{
		return m_FarPlane;
	}

	// recalculate view and projection matrix, using when changes position, yaw etc..
	virtual void RecalculateMatrices()
	{
		UpdateProjection();
		UpdateView();
	}

	//virtual void SetCameraTarget(Entity * target)
	//{
//		m_Target = target;
//	}

protected:
	glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
	glm::mat4 m_ViewMatrix = glm::mat4(1.0f);

	float m_Yaw, m_Pitch, m_Roll;

	float m_NearPlane = 0.1f;
	float m_FarPlane = 1000.f;

	float m_Fov, m_AspectRatio;

	float m_OnUpdate;

	glm::vec3 m_Position;

private:
	Entity* m_Target;
	glm::vec3 m_TargetPosition = { 0,0,1 };
};


/* EDITOR CAMERA */

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

enum class GameCameraType {
	FREE_CAMERA = 0, // TCL, like as Editor Camera
	FIRST_PERSON_CAMERA = 1, // camera in target position
	THIRD_PERSON_CAMERA, // camera view to target
	STATIC_VIEW_CAMERA // camera has a constant position
};



class EditorCamera
{
public:
	EditorCamera(glm::vec3 position, float aspectRatio, glm::vec3 up, glm::vec3 front, float fov, float nearplane, float farplane, glm::vec3 direction = glm::vec3(0.f));

	virtual ~EditorCamera();

	// TODO: Delete later empty method
	void OnUpdate(float DeltaTime, GLFWwindow* window);

	void Move(EditorCameraDirection direction,float DeltaTime);
	void Rotate(EditorCameraRotationDirection direction, float DeltaTime);

	// Change camera yaw and pitch (rotate) with mouse, (use in editor)
	void MousePan(const glm::vec2& delta);
	void MouseRotate(const glm::vec2& delta);

	std::pair<float, float> PanSpeed() const;

	// Use for viewport in editor
	void OnResize(float width, float height) {
		m_aspectRatio = width / height;
		Recalculate();
	}

	void Zoom(float ZoomFactor);

	void SetPosition(glm::vec3 position) { m_Position = position; Recalculate(); }


	// recalculate view and projection matrix, using when changes position, yaw etc..
	void Recalculate();

	const glm::vec3& GetPosition();

	// calculate position of camera , if she focused on target
	void CalculatePosition(float horizontalDistance, float verticalDistance);

	float& GetSpeed() { return m_MovementSpeed; }

	const glm::mat4& GetViewProjectionMatrix();
	const glm::mat4& GetViewMatrix() const;
	const glm::mat4& GetProjectionMatrix() const;

	float& GetFov();

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



