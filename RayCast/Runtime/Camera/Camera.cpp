#include "Camera.h"
#include "../Entity/Entity.h"



/* EDITOR CAMERA */

EditorCamera::EditorCamera(glm::vec3 position, float aspectRatio, glm::vec3 up, glm::vec3 front, float fov, float nearplane, float farplane, glm::vec3 direction)
    : m_Position(position),
    m_aspectRatio(aspectRatio),
    m_fov(fov),
    m_Up(up),
    m_nearPlane(nearplane),
    m_farPlane(farplane),
    m_cameraUp(glm::vec3(0.0f)),
    m_Front(front)
{
    this->m_viewMatrix = glm::mat4(1.0f);
    m_MovementSpeed = 11.0f;

    m_pitch = 0.f;
    m_yaw = -90.f;
    m_roll = 0.f;

    m_viewMatrix = glm::mat4(1.f);
    m_viewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);

    m_projectionMatrix = glm::mat4(1.f);
    m_projectionMatrix = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_nearPlane, m_farPlane);

    m_Right = glm::normalize(glm::cross(m_Front, m_Up));

}

EditorCamera::~EditorCamera()
{
}

void EditorCamera::OnUpdate(float DeltaTime,GLFWwindow* window)
{
    Recalculate();
}

void EditorCamera::Move(EditorCameraDirection direction, float DeltaTime)
{
    switch (direction)
    {
    case EditorCameraDirection::FORWARD:
        m_Position += m_MovementSpeed * m_Front * DeltaTime;
        break;
    case EditorCameraDirection::BACK:
        m_Position -= m_MovementSpeed * m_Front * DeltaTime;
        break;
    case EditorCameraDirection::UP:
        m_Position.y +=  m_MovementSpeed * DeltaTime;
        break;
    case EditorCameraDirection::DOWN:
        m_Position.y -= m_MovementSpeed * DeltaTime;
        break;
    case EditorCameraDirection::LEFT:
        m_Position -= glm::normalize(glm::cross(m_Front, m_Up)) * m_MovementSpeed * DeltaTime;
        break;
    case EditorCameraDirection::RIGHT:
        m_Position += glm::normalize(glm::cross(m_Front, m_Up)) * m_MovementSpeed * DeltaTime;
        break;
    default:
        break;
    }
    Recalculate();

}

void EditorCamera::Rotate(EditorCameraRotationDirection direction, float DeltaTime)
{
    Recalculate();
}

void EditorCamera::MousePan(const glm::vec2& delta)
{
    auto [xSpeed, ySpeed] = PanSpeed();
    m_Position += glm::normalize(glm::cross(m_Front, m_Up)) * delta.x * 0.01f;
    m_Position.y += delta.y * 0.01f;
  //  m_Position.y += 0.01f * delta.y * 1.f;
}

void EditorCamera::MouseRotate(const glm::vec2& delta)
{
    float yawSign = 0.1f;
    m_yaw += yawSign * delta.x * 0.8f;
    m_pitch += delta.y * 0.1f;

    if (m_pitch > 89.0f)
        m_pitch = 89.0f;
    if (m_pitch < -89.0f)
        m_pitch = -89.0f;

    glm::vec3 l_direction;
    l_direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    l_direction.y = sin(glm::radians(m_pitch));
    l_direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_Front = glm::normalize(l_direction);

    Recalculate();
}

std::pair<float, float> EditorCamera::PanSpeed() const
{
    float x = std::min(1920.f / 1000.0f, 2.4f); // max = 2.4f
    float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

    float y = std::min(1080.f / 1000.0f, 2.4f); // max = 2.4f
    float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

    return { xFactor, yFactor };

}

void EditorCamera::Zoom(float ScaleFactor)
{
    m_fov -= ScaleFactor;
    if (m_fov < 1.0f)
        m_fov = 1.0f;
    if (m_fov > 120.f)
        m_fov = 120.f;

    Recalculate();  
}

void EditorCamera::Recalculate()
{
    m_viewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
    m_projectionMatrix = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_nearPlane, m_farPlane);
}

const glm::vec3& EditorCamera::GetPosition()
{
    return m_Position;
}

void EditorCamera::CalculatePosition(float horizontalDistance, float verticalDistance)
{

}


const glm::mat4& EditorCamera::GetViewProjectionMatrix()
{
    return m_viewMatrix * m_projectionMatrix;
}

const glm::mat4& EditorCamera::GetViewMatrix() const
{
    return m_viewMatrix;
}

const glm::mat4& EditorCamera::GetProjectionMatrix() const
{
    return m_projectionMatrix;
}

float& EditorCamera::GetFov()
{
    return m_fov;
}

