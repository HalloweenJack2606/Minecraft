#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Core/Input.h"
#include "Core/Application.h"
#include <iostream>

namespace Minecraft
{
	InputState Input::s_Keys[1024];
	InputData Input::s_InputData;

	bool Input::IsKeyPressed(KeyCode key)
	{
		auto* window = Application::GetApp()->GetWindow().GetNativeWindow();
		auto state = glfwGetKey((GLFWwindow*)window, static_cast<s32>(key));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsKeyReleased(KeyCode key)
	{
		return s_Keys[key] == InputState::RELEASE;
	}

	bool Input::IsKeyUp(KeyCode key)
	{
		auto* window = Application::GetApp()->GetWindow().GetNativeWindow();
		auto state = glfwGetKey((GLFWwindow*)window, static_cast<s32>(key));
		return state == GLFW_RELEASE;
	}

	bool Input::IsMouseButtonPressed(MouseCode button)
	{
		auto* window = Application::GetApp()->GetWindow().GetNativeWindow();
		auto state = glfwGetMouseButton((GLFWwindow*)window, button);
		return state == GLFW_PRESS;
	}

	glm::vec2 Input::GetMousePosition()
	{
		auto* window = Application::GetApp()->GetWindow().GetNativeWindow();
		double xpos, ypos;
		glfwGetCursorPos((GLFWwindow*)window, &xpos, &ypos);

		return glm::vec2(xpos, ypos);
	}

	float Input::GetMouseX()
	{
		return GetMousePosition().x;
	}

	float Input::GetMouseY()
	{
		return GetMousePosition().y;
	}

	void Input::SetKey(KeyCode key, InputState state)
	{
		s_Keys[key] = state;
	}

	void Input::OnUpdate()
	{
		memset(s_Keys, (int)InputState::NONE, sizeof(InputState) * 1024);
		s_InputData.scrollX = 0.0;
		s_InputData.scrollY = 0.0;
	}
}