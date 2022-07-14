#include "stdafx.h"
#include "WindowsInput.h"



bool Input::IsKeyPressed(int key)
{
	auto* window = static_cast<GLFWwindow*>(Game::GetWindow().GetNativeWindow());
	auto keyState = glfwGetKey(window, static_cast<int32_t>(key));

	bool isPressed = keyState == GLFW_PRESS;
	bool isRepeated = keyState == GLFW_REPEAT;
	return isPressed || isRepeated;	
}

bool Input::IsMouseButtonPressed(int button)
{
	auto* window = static_cast<GLFWwindow*>(Game::GetWindow().GetNativeWindow());
	auto buttonState = glfwGetMouseButton	(window, static_cast<int32_t>(button));
	bool isPressed = buttonState == GLFW_PRESS;
	return isPressed;
}

glm::vec2 Input::GetMousePosition()
{
	auto* window = static_cast<GLFWwindow*>(Game::GetWindow().GetNativeWindow());
	
	double xPosition, yPosition;

	glfwGetCursorPos(window,&xPosition,&yPosition);

	return glm::vec2(xPosition, yPosition);
}

bool Input::GamepadIsConnected(unsigned int gamepad)
{
	return false;
}

bool Input::GamepadHasAxis(unsigned int gamepad, Gamepad::Axis axis)
{
	return false;
}

bool Input::GamepadIsButtonPressed(unsigned int gamepad, unsigned int button)
{
	return false;
}

float Input::GamepadGetAxisPosition(unsigned int gamepad, Gamepad::Axis axis)
{
	return 0.0f;
}
