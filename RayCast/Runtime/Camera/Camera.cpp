#include "Camera.h"

#include <iostream>

Camera::Camera(glm::vec3 position, float aspectRatio, glm::vec3 up, glm::vec3 front, float fov, float nearplane, float farplane, glm::vec3 direction)
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
    m_MovementSpeed = 3.0f;

    m_pitch = 0.f;
    m_yaw = -90.f;
    m_roll = 0.f;

    m_viewMatrix = glm::mat4(1.f);
    m_viewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up); 

    m_projectionMatrix = glm::mat4(1.f);
    m_projectionMatrix = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_nearPlane, m_farPlane);

    m_Right = glm::normalize(glm::cross(m_Front, m_Up));


}


Camera::~Camera()
{
}

void Camera::OnUpdate(float DeltaTime,GLFWwindow* window)
{
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        m_Position += m_MovementSpeed * m_Front * DeltaTime;    
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        m_Position -= m_MovementSpeed * m_Front * DeltaTime;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        m_Position -= glm::normalize(glm::cross(m_Front, m_Up)) * m_MovementSpeed * DeltaTime;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        m_Position += glm::normalize(glm::cross(m_Front, m_Up)) * m_MovementSpeed * DeltaTime;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        m_Position.y +=  m_MovementSpeed * DeltaTime;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        m_Position.y -= m_MovementSpeed * DeltaTime;

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        m_yaw += -35.f * DeltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        m_yaw += 35.f * DeltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        m_pitch += 35.f * DeltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        m_pitch += -35.f * DeltaTime;
    }

    glm::vec3 direction;
    direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    direction.y = sin(glm::radians(m_pitch));
    direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_Front = glm::normalize(direction);

    

    Recalculate();

}

void Camera::Move()
{
}

void Camera::Recalculate()
{
    m_viewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
    m_projectionMatrix = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_nearPlane, m_farPlane);
}

const glm::vec3& Camera::GetPosition()
{
    return m_Position;
}

void Camera::CalculatePosition(float horizontalDistance, float verticalDistance)
{

}


const glm::mat4& Camera::GetViewProjectionMatrix()
{
    return m_viewMatrix * m_projectionMatrix;
}

const glm::mat4& Camera::GetViewMatrix()
{

    return m_viewMatrix;
}

const glm::mat4& Camera::GetProjectionMatrix()
{
    return m_projectionMatrix;
}
